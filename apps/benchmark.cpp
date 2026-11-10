#include "benchmark/benchmark_function_factory.hpp"
#include "benchmark/benchmark_functions.hpp"
#include "core/optimizer_factory.hpp"
#include <map>
#include <iostream>

std::map<int, string> optimizer_names = {
    {1, "HO"},
    {2, "WOA"},
    {3, "GWO"},
};

std::map<int, string> function_names = {
    {1, "Sphere"},          {2, "Rosenbrock"},
    {3, "Rastrigin"},       {4, "Goldstein-Price"},
    {5, "Schwefel"},        {6, "Schwefel 222"},
    {7, "Eason"},           {8, "Michalewicz"},
    {9, "Hyper-Ellipsoid"}, {10, "Rotated Hyper-Ellipsoid"},
    {11, "Ackley"},         {12, "Griewank"},
    {13, "Branin"},         {14, "Six-Hump Camel"},
    {15, "Bukin N. 6"}, {16, "Cross-in-Tray"}, {17, "Drop-Wave"},
    {18, "Eggholder"}, {19, "Gramacy & Lee (2012)"}, {20, "Holder Table"},
    {21, "Langermann"}, {22, "Levy"}, {23, "Levy N. 13"},
    {24, "Schaeffer N. 2"}, {25, "Schaeffer N. 4"}, {26, "Shubert"},
    {27, "Bohachevsky"}, {28, "Perm 0,d,beta"}, {29, "Sum of Different Powers"},
    {30, "Sum Squares"}, {31, "Trid"}, {32, "Booth"}, {33, "Matyas"},
    {34, "McCormick"}, {35, "Power Sum"}, {36, "Zakharov"},
    {37, "Three-Hump Camel"}, {38, "Dixon-Price"}, {39, "De Jong N. 5"},
    {40, "Beale"}, {41, "Colville"}, {42, "Forrester et al. (2008)"},
    {43, "Hartmann 3-D"}, {44, "Hartmann 4-D"}, {45, "Hartmann 6-D"},
    {46, "Perm d,beta"}, {47, "Shekel"}, {48, "Powell"}, {49, "Styblinski-Tang"},
};

void print_usage(char** argv){
        std::cout << "Usage: " << argv[0] << " <optimizer_type> <function_type> <n_agents> <max_iterations>\n";
        std::cout << "Optimizer types:\n";
        std::cout << "1: HO\n";
        std::cout << "2: WOA\n";
        std::cout << "3: GWO\n";
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
        std::cout << "15: Bukin N. 6\n";
        std::cout << "16: Cross-in-Tray\n";
        std::cout << "17: Drop-Wave\n";
        std::cout << "18: Eggholder\n";
        std::cout << "19: Gramacy & Lee (2012)\n";
        std::cout << "20: Holder Table\n";
        std::cout << "21: Langermann\n";
        std::cout << "22: Levy\n";
        std::cout << "23: Levy N. 13\n";
        std::cout << "24: Schaeffer N. 2\n";
        std::cout << "25: Schaeffer N. 4\n";
        std::cout << "26: Shubert\n";
        std::cout << "27: Bohachevsky\n";
        std::cout << "28: Perm Function 0,d,beta\n";
        std::cout << "29: Sum of Different Powers\n";
        std::cout << "30: Sum Squares\n";
        std::cout << "31: Trid\n";
        std::cout << "32: Booth\n";
        std::cout << "33: Matyas\n";
        std::cout << "34: McCormick\n";
        std::cout << "35: Power Sum\n";
        std::cout << "36: Zakharov\n";
        std::cout << "37: Three-Hump Camel\n";
        std::cout << "38: Dixon-Price\n";
        std::cout << "39: De Jong N. 5\n";
        std::cout << "40: Beale\n";
        std::cout << "41: Colville\n";
        std::cout << "42: Forrester et al. (2008)\n";
        std::cout << "43: Hartmann 3-D\n";
        std::cout << "44: Hartmann 4-D\n";
        std::cout << "45: Hartmann 6-D\n";
        std::cout << "46: Perm Function d,beta\n";
        std::cout << "47: Shekel\n";
        std::cout << "48: Powell\n";
        std::cout << "49: Styblinski-Tang\n";

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

    if (function_type < 1 or function_type > 49) {
        std::cout << "Invalid function type. Please choose a number between 1 and 49.\n";
        print_usage(argv);
        return 1;
    }

    if (optimizer_type < 1 or optimizer_type > 3) {
        std::cout << "Invalid optimizer type. Please choose a number between 1 and 3.\n";
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
