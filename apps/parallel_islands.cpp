#include "benchmark/benchmark_function_factory.hpp"
#include "core/optimizer_factory.hpp"
#include "parallel-islands/policies.hpp"
#include "parallel-islands/parallel_island_manager.hpp"
#include "parallel-islands/parallel_island_runner.hpp"
#include <argparse/argparse.hpp>
#include <algorithm>
#include <iostream>
#include <memory>
#include <random>
#include <string>
#include <vector>

int
main(int argc, char **argv) {
    argparse::ArgumentParser parser("parallel_islands");
    parser.add_description("Run a population of optimizer islands with configurable migration and reconfiguration.");
    parser.add_epilog(
        "Policy values:\n"
        "  --topology: graph (all islands connected) or tree (binary tree)\n"
        "  --selection: bwr (best, worst, and random migrants)\n"
        "  --replacement: worst (replace the receiving island's worst candidates)\n"
        "  --reconfiguration: stagnated or none\n"
        "  --reconfiguration-choice: best\n\n"
        "Optimizer counts, population sizes, and iteration limits are set independently with\n"
        "--gwo / --gwo-agents / --gwo-iterations, --ho / --ho-agents / --ho-iterations, and\n"
        "--woa / --woa-agents / --woa-iterations. At least one island is required.\n"
        "--generations controls island-runner steps; each optimizer iteration option controls its\n"
        "optimizer's internal maximum iterations. All counts and iteration limits must be positive.\n\n"
        "Benchmark function IDs:\n"
        "  1 Sphere                 8 Michalewicz\n"
        "  2 Rosenbrock             9 Hyper-Ellipsoid\n"
        "  3 Rastrigin             10 Rotated Hyper-Ellipsoid\n"
        "  4 Goldstein-Price       11 Ackley\n"
        "  5 Schwefel              12 Griewank\n"
        "  6 Schwefel 2.22         13 Branin\n"
        "  7 Eason                 14 Six-Hump Camel\n\n"
        "Example: parallel_islands --function 3 --gwo 2 --gwo-agents 40 --ho 1 --ho-agents 30 "
        "--woa 1 --woa-agents 20 "
        "--gwo-iterations 100 --ho-iterations 80 --woa-iterations 120");
    parser.add_argument("--function", "-f")
        .help("benchmark function number (1-14)")
        .default_value(1)
        .scan<'i', int>();
    parser.add_argument("--gwo-agents")
        .help("number of agents in each GWO island")
        .default_value(size_t{30})
        .scan<'i', size_t>();
    parser.add_argument("--ho-agents")
        .help("number of agents in each HO island")
        .default_value(size_t{30})
        .scan<'i', size_t>();
    parser.add_argument("--woa-agents")
        .help("number of agents in each WOA island")
        .default_value(size_t{30})
        .scan<'i', size_t>();
    parser.add_argument("--generations", "-g")
        .help("number of generations")
        .default_value(size_t{100})
        .scan<'i', size_t>();
    parser.add_argument("--migration-rate")
        .help("migration interval in generations")
        .default_value(size_t{10})
        .scan<'i', size_t>();
    parser.add_argument("--reconfiguration-rate")
        .help("reconfiguration interval in generations")
        .default_value(size_t{10})
        .scan<'i', size_t>();
    parser.add_argument("--gwo")
        .help("number of GWO optimizers to create")
        .default_value(size_t{1})
        .scan<'i', size_t>();
    parser.add_argument("--ho")
        .help("number of HO optimizers to create")
        .default_value(size_t{1})
        .scan<'i', size_t>();
    parser.add_argument("--woa")
        .help("number of WOA optimizers to create")
        .default_value(size_t{1})
        .scan<'i', size_t>();
    parser.add_argument("--gwo-iterations")
        .help("maximum iterations for each GWO optimizer")
        .default_value(size_t{60})
        .scan<'i', size_t>();
    parser.add_argument("--ho-iterations")
        .help("maximum iterations for each HO optimizer")
        .default_value(size_t{60})
        .scan<'i', size_t>();
    parser.add_argument("--woa-iterations")
        .help("maximum iterations for each WOA optimizer")
        .default_value(size_t{60})
        .scan<'i', size_t>();
    parser.add_argument("--topology")
        .help("island topology: graph or tree")
        .default_value(std::string("graph"));
    parser.add_argument("--selection")
        .help("migration selection policy: bwr")
        .default_value(std::string("bwr"));
    parser.add_argument("--replacement")
        .help("migration replacement policy: worst")
        .default_value(std::string("worst"));
    parser.add_argument("--reconfiguration")
        .help("reconfiguration policy: none or stagnated")
        .default_value(std::string("stagnated"));
    parser.add_argument("--reconfiguration-choice")
        .help("optimizer choice policy for reconfiguration: best")
        .default_value(std::string("best"));

    try {
        parser.parse_args(argc, argv);
    } catch (const std::exception &err) {
        std::cerr << err.what() << '\n' << parser;
        return 1;
    }

    const int function_type = parser.get<int>("--function");
    const size_t gwo_agents = parser.get<size_t>("--gwo-agents");
    const size_t ho_agents = parser.get<size_t>("--ho-agents");
    const size_t woa_agents = parser.get<size_t>("--woa-agents");
    const size_t n_generations = parser.get<size_t>("--generations");
    const size_t migration_rate = parser.get<size_t>("--migration-rate");
    const size_t reconfiguration_rate = parser.get<size_t>("--reconfiguration-rate");
    const size_t n_gwo = parser.get<size_t>("--gwo");
    const size_t n_ho = parser.get<size_t>("--ho");
    const size_t n_woa = parser.get<size_t>("--woa");
    const size_t gwo_iterations = parser.get<size_t>("--gwo-iterations");
    const size_t ho_iterations = parser.get<size_t>("--ho-iterations");
    const size_t woa_iterations = parser.get<size_t>("--woa-iterations");
    const auto topology = parser.get<std::string>("--topology");
    const auto selection = parser.get<std::string>("--selection");
    const auto replacement = parser.get<std::string>("--replacement");
    const auto reconfiguration = parser.get<std::string>("--reconfiguration");
    const auto reconfiguration_choice = parser.get<std::string>("--reconfiguration-choice");

    if (function_type < 1 || function_type > 14 || (n_gwo > 0 && gwo_agents == 0) ||
        (n_ho > 0 && ho_agents == 0) || (n_woa > 0 && woa_agents == 0) || n_generations == 0 ||
        n_gwo + n_ho + n_woa == 0 || gwo_iterations == 0 || ho_iterations == 0 || woa_iterations == 0) {
        std::cerr << "Function must be 1-14; agent counts, generations, and optimizer iterations must be positive; "
                     "and at least one optimizer is required.\n";
        return 1;
    }
    if ((topology != "graph" && topology != "tree") || selection != "bwr" || replacement != "worst" ||
        (reconfiguration != "none" && reconfiguration != "stagnated") || reconfiguration_choice != "best") {
        std::cerr << "Unsupported policy value. See --help for available policies.\n";
        return 1;
    }

    const size_t island_count = n_gwo + n_ho + n_woa;
    std::vector<HomogeneousIsland> islands;
    islands.reserve(island_count);
    auto add_islands = [&](int optimizer_type, size_t count, size_t n_agents, size_t max_iterations) {
        for (size_t i = 0; i < count; ++i) {
            islands.emplace_back(OptimizerFactory::create(optimizer_type, n_agents, max_iterations,
                                                          BenchmarkFunctionFactory::create(function_type)));
        }
    };
    add_islands(GWO, n_gwo, gwo_agents, gwo_iterations);
    add_islands(HO, n_ho, ho_agents, ho_iterations);
    add_islands(WOA, n_woa, woa_agents, woa_iterations);

    std::random_device random_device;
    std::mt19937 random_engine(random_device());
    std::shuffle(islands.begin(), islands.end(), random_engine);

    std::unique_ptr<TopologyPolicyInterface> topology_policy;
    if (topology == "graph") {
        topology_policy = std::make_unique<TopologyCompleteGraph>(islands);
    } else {
        topology_policy = std::make_unique<TopologyCompleteTree>(islands);
    }
    std::unique_ptr<ReconfigurationPolicyInterface> reconfiguration_policy;
    if (reconfiguration == "stagnated") {
        reconfiguration_policy = std::make_unique<ReconfigurationReconfigureStagnated>();
    } else {
        reconfiguration_policy = std::make_unique<ReconfigurationReconfigureNone>();
    }
    auto manager = ParallelIslandManager(std::move(topology_policy), std::make_unique<SelectionBWR>(),
                                         std::make_unique<ReplaceWorst>(), std::move(reconfiguration_policy),
                                         std::make_unique<ReconfigurationChoiceBest>());
    ParallelIslandRunner runner(island_count, std::move(islands), n_generations, migration_rate,
                                reconfiguration_rate);
    runner.set_manager(std::move(manager));
    runner.run();
    return 0;
}
