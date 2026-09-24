#ifndef BENCHMARK_FUNCTIONS_H
#define BENCHMARK_FUNCTIONS_H

#include "core/problem.hpp"
#include "ho/function.hpp" // TODO Change this
#include <cstdint>
#include <string>
#include <vector>
using vd = std::vector<double>;
using std::string;

class BenchmarkFunctionBase : public ProblemBase {
  public:
    using ::ProblemBase::ProblemBase; // Inherit constructors
    virtual string name() const = 0;
    virtual string description() const = 0;
    std::tuple<uint32_t, vd, vd, std::function<double(const vd &)>> get_info() const {
        return std::make_tuple(n_dimensions_, lowerbound_, upperbound_, f_);
    }
};

class SphereFunction : public BenchmarkFunctionBase {
  public:
    SphereFunction();
    string name() const override;
    string description() const override;
    std::unique_ptr<ProblemBase> clone() const override;
};

class RosenbrockFunction : public BenchmarkFunctionBase {
  public:
    RosenbrockFunction();
    string name() const override;
    string description() const override;
    std::unique_ptr<ProblemBase> clone() const override;
};

class RastriginFunction : public BenchmarkFunctionBase {
  public:
    RastriginFunction();
    string name() const override;
    string description() const override;
    std::unique_ptr<ProblemBase> clone() const override;
};

class GoldsteinPriceFunction : public BenchmarkFunctionBase {
  public:
    GoldsteinPriceFunction();
    string name() const override;
    string description() const override;
    std::unique_ptr<ProblemBase> clone() const override;
};

/**
 * @brief  Shifted Schwefel function
 */
class SchwefelFunction : public BenchmarkFunctionBase {
  public:
    SchwefelFunction();
    string name() const override;
    string description() const override;
    std::unique_ptr<ProblemBase> clone() const override;
};

class Schwefel222Function : public BenchmarkFunctionBase {
  public:
    Schwefel222Function();
    string name() const override;
    string description() const override;
    std::unique_ptr<ProblemBase> clone() const override;
};

/**
 * @brief Eason's Function. Global minimum f(x)=-1 at (pi,pi)
 */
class EasonFunction : public BenchmarkFunctionBase {
  public:
    EasonFunction();
    string name() const override;
    string description() const override;
    std::unique_ptr<ProblemBase> clone() const override;
};

class MichalewiczFunction : public BenchmarkFunctionBase {
  public:
    MichalewiczFunction();
    string name() const override;
    string description() const override;
    std::unique_ptr<ProblemBase> clone() const override;
};

class HyperEllipsoidFunction : public BenchmarkFunctionBase {
  public:
    HyperEllipsoidFunction();
    string name() const override;
    string description() const override;
    std::unique_ptr<ProblemBase> clone() const override;
};
class RotatedHyperEllipsoidFunction : public BenchmarkFunctionBase {
  public:
    RotatedHyperEllipsoidFunction();
    string name() const override;
    string description() const override;
    std::unique_ptr<ProblemBase> clone() const override;
};

class AckleyFunction : public BenchmarkFunctionBase {
  public:
    AckleyFunction();
    string name() const override;
    string description() const override;
    std::unique_ptr<ProblemBase> clone() const override;
};

class GriewankFunction : public BenchmarkFunctionBase {
  public:
    GriewankFunction();
    string name() const override;
    string description() const override;
    std::unique_ptr<ProblemBase> clone() const override;
};

class BraninFunction : public BenchmarkFunctionBase {
  public:
    BraninFunction();
    string name() const override;
    string description() const override;
    std::unique_ptr<ProblemBase> clone() const override;
};

class SixHumpCamelFunction : public BenchmarkFunctionBase {
  public:
    SixHumpCamelFunction();
    string name() const override;
    string description() const override;
    std::unique_ptr<ProblemBase> clone() const override;
};

#endif // BENCHMARK_FUNCTIONS_H