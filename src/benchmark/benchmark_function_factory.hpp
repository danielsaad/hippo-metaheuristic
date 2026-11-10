#ifndef BENCHMARK_FUNCTION_FACTORY_H
#define BENCHMARK_FUNCTION_FACTORY_H
#include "benchmark_functions.hpp"
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
    SIX_HUMP_CAMEL,
    BUKIN_N6,
    CROSS_IN_TRAY,
    DROP_WAVE,
    EGGHOLDER,
    GRAMACY_LEE,
    HOLDER_TABLE,
    LANGERMANN,
    LEVY,
    LEVY_N13,
    SCHAEFFER_N2,
    SCHAEFFER_N4,
    SHUBERT,
    BOHACHEVSKY,
    PERM_0DB,
    SUM_DIFFERENT_POWERS,
    SUM_SQUARES,
    TRID,
    BOOTH,
    MATYAS,
    MCCORMICK,
    POWER_SUM,
    ZAKHAROV,
    THREE_HUMP_CAMEL,
    DIXON_PRICE,
    DE_JONG_N5,
    BEALE,
    COLVILLE,
    FORRESTER_2008,
    HARTMANN_3D,
    HARTMANN_4D,
    HARTMANN_6D,
    PERM_DB,
    SHEKEL,
    POWELL,
    STYBLINSKI_TANG
};

class BenchmarkFunctionFactory {
  public:
    static std::unique_ptr<BenchmarkFunctionBase>
    create(int type);
};

#endif
