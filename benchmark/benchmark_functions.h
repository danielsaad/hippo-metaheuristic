#ifndef BENCHMARK_FUNCTIONS_H
#define BENCHMARK_FUNCTIONS_H

#include "function.h"
#include <cstdint>
#include <vector>
using vd = std::vector<double>;

class benchmark_function {
  public:
    benchmark_function() : n_dimensions(0), lowerbound(), upperbound(), f(nullptr) {}
    uint32_t n_dimensions;
    vd lowerbound;
    vd upperbound;
    fun f;
    virtual void set_f() = 0;
    std::tuple<uint32_t, vd, vd, fun> get_info() const {
        return std::make_tuple(n_dimensions, lowerbound, upperbound, f);
    }
};

class sphere_function : public benchmark_function {
    public:
        sphere_function();
        void set_f() override;
};


class rosenbrock_function : public benchmark_function {
  public:
    rosenbrock_function();
    void set_f() override;
};

class rastrigin_function : public benchmark_function {
  public:
    rastrigin_function();
    void set_f() override;
};

class goldstein_price_function : public benchmark_function {
  public:
    goldstein_price_function();
    void set_f() override;
};
#endif // BENCHMARK_FUNCTIONS_H