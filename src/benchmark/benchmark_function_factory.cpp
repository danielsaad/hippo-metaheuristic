#include "benchmark/benchmark_function_factory.hpp"
#include "benchmark/benchmark_functions.hpp"
#include <memory>

std::unique_ptr<BenchmarkFunctionBase> BenchmarkFunctionFactory::create(int type) {
    switch (type) {
    case SPHERE:
        return std::make_unique<SphereFunction>();
    case ROSENBROCK:
        return std::make_unique<RosenbrockFunction>();
    case RASTRIGIN:
        return std::make_unique<RastriginFunction>();
    case GOLDSTEIN_PRICE:
        return std::make_unique<GoldsteinPriceFunction>();
    case SCHWEFEL:
        return std::make_unique<SchwefelFunction>();
    case SCHWEFEL_222:
        return std::make_unique<Schwefel222Function>();
    case EASON:
        return std::make_unique<EasonFunction>();
    case MICHALEWICZ:
        return std::make_unique<MichalewiczFunction>();
    case HYPER_ELLIPSOID:
        return std::make_unique<HyperEllipsoidFunction>();
    case ROTATED_HYPER_ELLIPSOID:
        return std::make_unique<RotatedHyperEllipsoidFunction>();
    case ACKLEY:
        return std::make_unique<AckleyFunction>();
    case GRIEWANK:
        return std::make_unique<GriewankFunction>();
    case BRANIN:
        return std::make_unique<BraninFunction>();
    case SIX_HUMP_CAMEL:
        return std::make_unique<SixHumpCamelFunction>();
    default:
        return nullptr;
    }
}
