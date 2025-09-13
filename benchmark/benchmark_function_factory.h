#ifndef BENCHMARK_FUNCTION_FACTORY_H
#define BENCHMARK_FUNCTION_FACTORY_H
#include "benchmark_functions.h"
#include <memory>

enum {
    SPHERE = 1,
    ROSENBROCK,
    RASTRIGIN,
    GOLDSTEIN_PRICE,
    SCHWEFEL,
    SCHWEFEL_222,
    EASON,
    MICHALEWICZ,
    HYPER_ELLIPSOID,
    ROTATED_HYPER_ELLIPSOID,
    ACKLEY,
    GRIEWANK,
    BRANIN,
    SIX_HUMP_CAMEL
};

class benchmark_function_factory {
    public:
        static std::unique_ptr<benchmark_function> create(int type);
};

#endif