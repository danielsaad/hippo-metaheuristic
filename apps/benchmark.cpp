#include "benchmark/benchmark_function_factory.hpp"
#include "benchmark/benchmark_functions.hpp"
#include "core/optimizer_factory.hpp"
#include <map>
#include <iostream>

std::map<int, string> optimizer_names = {
    {1, "HO"},
    {2, "WOA"},
};

std::map<int, string> function_names = {
    {1, "Sphere"},          {2, "Rosenbrock"},
    {3, "Rastrigin"},       {4, "Goldstein-Price"},
    {5, "Schwefel"},        {6, "Schwefel 222"},
    {7, "Eason"},           {8, "Michalewicz"},
    {9, "Hyper-Ellipsoid"}, {10, "Rotated Hyper-Ellipsoid"},
    {11, "Ackley"},         {12, "Griewank"},
    {13, "Branin"},         {14, "Six-Hump Camel"},
};

void print_usage(char** argv){
        std::cout << "Usage: " << argv[0] << " <optimizer_type> <function_type> <n_agents> <max_iterations>\n";
        std::cout << "Optimizer types:\n";
        std::cout << "1: HO\n";
        std::cout << "2: WOA\n";
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
    int optimizer_type = std::atoi(argv[1]);
    int function_type = std::atoi(argv[2]);
    size_t n_agents = std::atoi(argv[3]);
    size_t max_iterations = std::atoi(argv[4]);

    if (function_type < 1 || function_type > 14) {
        std::cout << "Invalid function type. Please choose a number between 1 and 14.\n";
        print_usage(argv);
        return 1;
    }

    if (optimizer_type < 1 || optimizer_type > 2) {
        std::cout << "Invalid optimizer type. Please choose a number between 1 and 2.\n";
        print_usage(argv);
        return 1;
    }

    auto objective_function = BenchmarkFunctionFactory::create(function_type);
    auto optimizer =
        OptimizerFactory::create(optimizer_type, n_agents, max_iterations, std::move(objective_function));
    std::cout << "Evaluating function " << function_names[function_type] << " using optimizer "
              << optimizer_names[optimizer_type] << "\n";
    optimizer->run();
    auto [best_position, best_value] = optimizer->get_best_solution();
    std::cout << "Best solution found:\n";
    std::cout << "Position: ";
    for (const auto &x : best_position) {
        std::cout << x << " ";
    }
    std::cout << "\nValue: " << best_value << "\n";
    return 0;
}
