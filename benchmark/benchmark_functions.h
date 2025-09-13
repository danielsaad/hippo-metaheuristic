#ifndef BENCHMARK_FUNCTIONS_H
#define BENCHMARK_FUNCTIONS_H

#include "function.h"
#include <cstdint>
#include <vector>
#include <string>
using vd = std::vector<double>;
using std::string;

class benchmark_function {
  public:
    benchmark_function() : n_dimensions(0), lowerbound(), upperbound(), f(nullptr) {}
    uint32_t n_dimensions;
    vd lowerbound;
    vd upperbound;
    fun f;
    virtual string name() const = 0;
    virtual string description() const = 0;
    virtual void set_f() = 0;
    std::tuple<uint32_t, vd, vd, fun> get_info() const {
        return std::make_tuple(n_dimensions, lowerbound, upperbound, f);
    }
};

class sphere_function : public benchmark_function {
  public:
    sphere_function();
    string name() const override;
    string description() const override;
    void set_f() override;
};

class rosenbrock_function : public benchmark_function {
  public:
    rosenbrock_function();
    string name() const override;
    string description() const override;
    void set_f() override;
};

class rastrigin_function : public benchmark_function {
  public:
    rastrigin_function();
    string name() const override;
    string description() const override;
    void set_f() override;
};

class goldstein_price_function : public benchmark_function {
  public:
    goldstein_price_function();
    string name() const override;
    string description() const override;
    void set_f() override;
};

/**
 * @brief  Shifted Schwefel function
 */
class schwefel_function : public benchmark_function {
  public:
    schwefel_function();
    string name() const override;
    string description() const override;
    void set_f() override;
};

class schwefel_222_function : public benchmark_function {
  public:
    schwefel_222_function();
    string name() const override;
    string description() const override;
    void set_f() override;
};

/**
 * @brief Eason's Function. Global minimum f(x)=-1 at (pi,pi)
 */
class eason_function:public benchmark_function{
  public:
    eason_function();
    string name() const override;
    string description() const override;
    void set_f() override;
};

#endif // BENCHMARK_FUNCTIONS_H