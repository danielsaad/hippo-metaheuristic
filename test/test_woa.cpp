#include "benchmark/benchmark_functions.hpp"
#include "woa/woa.hpp"

int main() {
    // Example usage of WOA
    Woa woa_instance(30, 100, -10.0, 10.0, 2, benchmark_functions::sphere);
    woa_instance.run();
    return 0;
}