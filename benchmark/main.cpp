#include "benchmark_function_factory.h"
#include "benchmark_functions.h"
#include "hippo_optimizer.h"

int main() {
    const int n_hippo = 16;
    const int max_iterations = 500;
    // vector<int> function_types = {
    //     SPHERE, ROSENBROCK,  RASTRIGIN,       GOLDSTEIN_PRICE,         SCHWEFEL, SCHWEFEL_222,
    //     EASON,  MICHALEWICZ, HYPER_ELLIPSOID, ROTATED_HYPER_ELLIPSOID, ACKLEY, BRANIN, SIX_HUMP_CAMEL};
    vector<int> function_types = {SIX_HUMP_CAMEL};
    for (const auto &t : function_types) {
        auto benchmark_function = benchmark_function_factory::create(t);
        std::cout << "Evaluating function " << benchmark_function->name() << "\n";
        std::cout << "Description: " << benchmark_function->description() << "\n";
        auto [n_dimensions, lowerbound, upperbound, f] = benchmark_function->get_info();
        hippo_optimizer optimizer(n_hippo, max_iterations, lowerbound[0], upperbound[0], n_dimensions, f);
        optimizer.run();
    }
}