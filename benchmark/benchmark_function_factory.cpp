#include "benchmark_function_factory.h"
#include "benchmark_functions.h"
#include <memory>

std::unique_ptr<benchmark_function> benchmark_function_factory::create(int type) {
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
    case MICHALEWICZ:
        return std::make_unique<michalewicz_function>();
    case HYPER_ELLIPSOID:
        return std::make_unique<hyper_ellipsoid_function>();
    case ROTATED_HYPER_ELLIPSOID:
        return std::make_unique<rotated_hyper_ellipsoid_function>();
    case ACKLEY:
        return std::make_unique<ackley_function>();
    case GRIEWANK:
        return std::make_unique<griewank_function>();
    case BRANIN:
        return std::make_unique<branin_function>();
    case SIX_HUMP_CAMEL:
        return std::make_unique<six_hump_camel_function>();
    default:
        return nullptr;
    }
}
