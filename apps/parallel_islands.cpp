#include "benchmark/benchmark_function_factory.hpp"
#include "core/optimizer_factory.hpp"
#include "parallel-islands/parallel_island_manager.hpp"
#include "parallel-islands/parallel_island_runner.hpp"
#include "parallel-islands/replace_worst.hpp"
#include "parallel-islands/selection_bwr.hpp"
#include "parallel-islands/topology_complete_tree.hpp"
#include "parallel-islands/topology_complete_graph.hpp"
#include <iostream>
#include <map>
#include <memory>
#include <print>
#include <thread>

std::map<int, string> function_names = {
    {1, "Sphere"},          {2, "Rosenbrock"},
    {3, "Rastrigin"},       {4, "Goldstein-Price"},
    {5, "Schwefel"},        {6, "Schwefel 222"},
    {7, "Eason"},           {8, "Michalewicz"},
    {9, "Hyper-Ellipsoid"}, {10, "Rotated Hyper-Ellipsoid"},
    {11, "Ackley"},         {12, "Griewank"},
    {13, "Branin"},         {14, "Six-Hump Camel"},
};

void print_usage(char **argv) {
    std::cout << "Usage: " << argv[0] << "<function_type> <n_agents> <n_generations> <migration_rate>\n";
    std::cout << "Function types:\n";
    std::cout << "1: Sphere\n";
    std::cout << "2: Rosenbrock\n";
    std::cout << "3: Rastrigin\n";
    std::cout << "4: Goldstein-Price\n";
    std::cout << "5: Schwefel\n";
    std::cout << "6: Schwefel 222\n";
    std::cout << "7: Eason\n";
    std::cout << "8: Michalewicz\n";
    std::cout << "9: Hyper-Ellipsoid\n";
    std::cout << "10: Rotated Hyper-Ellipsoid\n";
    std::cout << "11: Ackley\n";
    std::cout << "12: Griewank\n";
    std::cout << "13: Branin\n";
    std::cout << "14: Six-Hump Camel\n";
}

int main(int argc, char **argv) {
    if (argc < 5) {
        print_usage(argv);
        return 1;
    }
    std::print("Test\n");
    int function_type = std::atoi(argv[1]);
    size_t n_agents = std::atoi(argv[2]);
    size_t n_generations = std::atoi(argv[3]);
    size_t migration_rate = std::atoi(argv[4]);
    size_t thread_n = std::thread::hardware_concurrency();
    if (function_type < 1 || function_type > 14) {
        std::cout << "Invalid function type. Please choose a number between 1 and 14.\n";
        print_usage(argv);
        return 1;
    }

    vector<std::unique_ptr<OptimizerBase>> optimizers;
    std::vector<HomogeneousIsland> islands;
    islands.reserve(thread_n);
    const int max_it = 60;
    vector<size_t> island_max_it = {max_it, max_it};
    for (size_t i = 0; i < thread_n; i++) {
        auto opt = OptimizerFactory::create(1 , n_agents, island_max_it[i % 2],
                                            BenchmarkFunctionFactory::create(function_type));
        islands.emplace_back(HomogeneousIsland(std::move(opt)));
    }

    ManagerPolicy manager(std::make_unique<TopologyCompleteTree>(islands), std::make_unique<ReplaceWorst>(),
                          std::make_unique<SelectionBWR>());
    ParallelIslandRunner island_runner(thread_n, std::move(islands), n_generations, migration_rate);
    ParallelIslandManager island_manager(std::move(manager));
    island_runner.set_policy(std::move(island_manager));
    island_runner.run();
    return 0;
}