#include "benchmark/benchmark_function_factory.hpp"
#include "core/optimizer_factory.hpp"
#include "parallel-islands/policies.hpp"
#include "parallel-islands/parallel_island_manager.hpp"
#include "parallel-islands/parallel_island_runner.hpp"
#include <argparse/argparse.hpp>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

int
main(int argc, char **argv) {
    argparse::ArgumentParser parser("parallel_islands");
    parser.add_argument("--function", "-f")
        .help("benchmark function number (1-14)")
        .default_value(1)
        .scan<'i', int>();
    parser.add_argument("--agents", "-a")
        .help("population size per island")
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
    const size_t n_agents = parser.get<size_t>("--agents");
    const size_t n_generations = parser.get<size_t>("--generations");
    const size_t migration_rate = parser.get<size_t>("--migration-rate");
    const size_t reconfiguration_rate = parser.get<size_t>("--reconfiguration-rate");
    const size_t n_gwo = parser.get<size_t>("--gwo");
    const size_t n_ho = parser.get<size_t>("--ho");
    const size_t n_woa = parser.get<size_t>("--woa");
    const auto topology = parser.get<std::string>("--topology");
    const auto selection = parser.get<std::string>("--selection");
    const auto replacement = parser.get<std::string>("--replacement");
    const auto reconfiguration = parser.get<std::string>("--reconfiguration");
    const auto reconfiguration_choice = parser.get<std::string>("--reconfiguration-choice");

    if (function_type < 1 || function_type > 14 || n_agents == 0 || n_generations == 0 ||
        n_gwo + n_ho + n_woa == 0) {
        std::cerr << "Function must be 1-14, agents and generations must be positive, and at least one "
                     "optimizer is required.\n";
        return 1;
    }
    if ((topology != "graph" && topology != "tree") || selection != "bwr" || replacement != "worst" ||
        (reconfiguration != "none" && reconfiguration != "stagnated") || reconfiguration_choice != "best") {
        std::cerr << "Unsupported policy value. See --help for available policies.\n";
        return 1;
    }

    const size_t island_count = n_gwo + n_ho + n_woa;
    constexpr size_t max_iterations = 60;
    std::vector<HomogeneousIsland> islands;
    islands.reserve(island_count);
    auto add_islands = [&](int optimizer_type, size_t count) {
        for (size_t i = 0; i < count; ++i) {
            islands.emplace_back(OptimizerFactory::create(optimizer_type, n_agents, max_iterations,
                                                          BenchmarkFunctionFactory::create(function_type)));
        }
    };
    add_islands(GWO, n_gwo);
    add_islands(HO, n_ho);
    add_islands(WOA, n_woa);

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
