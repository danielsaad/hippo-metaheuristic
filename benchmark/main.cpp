#include "benchmark_functions.h"
#include "hippo_optimizer.h"

int main() {
    const int n_hippo = 16;
    const int max_iterations = 500;
    auto [n_dimensions, lowerbound, upperbound, f] = goldstein_price_function().get_info();
    hippo_optimizer optimizer(n_hippo, max_iterations, lowerbound[0], upperbound[0], n_dimensions, f);
    optimizer.run();
}