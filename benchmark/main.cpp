#include "benchmark_function_factory.h"
#include "benchmark_functions.h"
#include "hippo_optimizer.h"

int main(int argc, char **argv) {
    if (argc < 2) {
        std::cout << "Usage: " << argv[0] << " <function_type>\n";
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
        std::cout << "12: Branin\n";
        std::cout << "13: Six-Hump Camel\n";
        return 1;
    }
    int t = std::atoi(argv[1]);
    if (t < 1 || t > 13) {
        std::cout << "Invalid function type. Please choose a number between 1 and 13.\n";
        return 1;
    }
    const int n_hippo = 16;
    const int max_iterations = 500;
    auto benchmark_function = benchmark_function_factory::create(t);
    std::cout << "Evaluating function " << benchmark_function->name() << "\n";
    std::cout << "Description: " << benchmark_function->description() << "\n";
    auto [n_dimensions, lowerbound, upperbound, f] = benchmark_function->get_info();
    hippo_optimizer optimizer(n_hippo, max_iterations, lowerbound[0], upperbound[0], n_dimensions, f);
    optimizer.run();
    auto [best_solution, best_fitness] = optimizer.get_best_solution();
    std::cout << benchmark_function->name() << std::endl;
    std::cout << best_fitness << "\n";
    std::cout << "(";
    for (size_t i = 0; i < best_solution.size(); i++) {
        std::cout << best_solution[i] << ",)"[i == best_solution.size() - 1];
    }
    std::cout << "\n";
    return 0;
}