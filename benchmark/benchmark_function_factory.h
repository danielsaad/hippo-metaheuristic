#ifndef BENCHMARK_FUNCTION_FACTORY_H
#define BENCHMARK_FUNCTION_FACTORY_H
#include "benchmark_functions.h"
#include <memory>

enum { SPHERE = 1, ROSENBROCK, RASTRIGIN, GOLDSTEIN_PRICE, SCHWEFEL, SCHWEFEL_222, EASON };

class benchmark_function_factory {
  public:
    static std::unique_ptr<benchmark_function> create(int type) {
        switch (type) {
        case SPHERE:
            return std::make_unique<sphere_function>();
        case ROSENBROCK:
            return std::make_unique<rosenbrock_function>();
        case RASTRIGIN:
            return std::make_unique<rastrigin_function>();
        case GOLDSTEIN_PRICE:
            return std::make_unique<goldstein_price_function>();
        case SCHWEFEL:
            return std::make_unique<schwefel_function>();
        case SCHWEFEL_222:
            return std::make_unique<schwefel_222_function>();
        case EASON:
            return std::make_unique<eason_function>();
        default:
            return nullptr;
        }
    }
};

#endif