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
    virtual string
    name() const = 0;
    virtual string
    description() const = 0;

    std::tuple<uint32_t, vd, vd, std::function<double(const vd &)>>
    get_info() const {
        return std::make_tuple(n_dimensions_, lowerbound_, upperbound_, f_);
    }
};

class SphereFunction : public BenchmarkFunctionBase {
  public:
    SphereFunction();
    string
    name() const override;
    string
    description() const override;
    std::unique_ptr<ProblemBase>
    clone() const override;
};

class RosenbrockFunction : public BenchmarkFunctionBase {
  public:
    RosenbrockFunction();
    string
    name() const override;
    string
    description() const override;
    std::unique_ptr<ProblemBase>
    clone() const override;
};

class RastriginFunction : public BenchmarkFunctionBase {
  public:
    RastriginFunction();
    string
    name() const override;
    string
    description() const override;
    std::unique_ptr<ProblemBase>
    clone() const override;
};

class GoldsteinPriceFunction : public BenchmarkFunctionBase {
  public:
    GoldsteinPriceFunction();
    string
    name() const override;
    string
    description() const override;
    std::unique_ptr<ProblemBase>
    clone() const override;
};

/**
 * @brief  Shifted Schwefel function
 */
class SchwefelFunction : public BenchmarkFunctionBase {
  public:
    SchwefelFunction();
    string
    name() const override;
    string
    description() const override;
    std::unique_ptr<ProblemBase>
    clone() const override;
};

class Schwefel222Function : public BenchmarkFunctionBase {
  public:
    Schwefel222Function();
    string
    name() const override;
    string
    description() const override;
    std::unique_ptr<ProblemBase>
    clone() const override;
};

/**
 * @brief Eason's Function. Global minimum f(x)=-1 at (pi,pi)
 */
class EasonFunction : public BenchmarkFunctionBase {
  public:
    EasonFunction();
    string
    name() const override;
    string
    description() const override;
    std::unique_ptr<ProblemBase>
    clone() const override;
};

class MichalewiczFunction : public BenchmarkFunctionBase {
  public:
    MichalewiczFunction();
    string
    name() const override;
    string
    description() const override;
    std::unique_ptr<ProblemBase>
    clone() const override;
};

class HyperEllipsoidFunction : public BenchmarkFunctionBase {
  public:
    HyperEllipsoidFunction();
    string
    name() const override;
    string
    description() const override;
    std::unique_ptr<ProblemBase>
    clone() const override;
};

class RotatedHyperEllipsoidFunction : public BenchmarkFunctionBase {
  public:
    RotatedHyperEllipsoidFunction();
    string
    name() const override;
    string
    description() const override;
    std::unique_ptr<ProblemBase>
    clone() const override;
};

class AckleyFunction : public BenchmarkFunctionBase {
  public:
    AckleyFunction();
    string
    name() const override;
    string
    description() const override;
    std::unique_ptr<ProblemBase>
    clone() const override;
};

class GriewankFunction : public BenchmarkFunctionBase {
  public:
    GriewankFunction();
    string
    name() const override;
    string
    description() const override;
    std::unique_ptr<ProblemBase>
    clone() const override;
};

class BraninFunction : public BenchmarkFunctionBase {
  public:
    BraninFunction();
    string
    name() const override;
    string
    description() const override;
    std::unique_ptr<ProblemBase>
    clone() const override;
};

class SixHumpCamelFunction : public BenchmarkFunctionBase {
  public:
    SixHumpCamelFunction();
    string
    name() const override;
    string
    description() const override;
    std::unique_ptr<ProblemBase>
    clone() const override;
};

class BukinN6Function : public BenchmarkFunctionBase {
  public:
    BukinN6Function();
    string name() const override;
    string description() const override;
    std::unique_ptr<ProblemBase> clone() const override;
};

class CrossInTrayFunction : public BenchmarkFunctionBase {
  public:
    CrossInTrayFunction();
    string name() const override;
    string description() const override;
    std::unique_ptr<ProblemBase> clone() const override;
};

class DropWaveFunction : public BenchmarkFunctionBase {
  public:
    DropWaveFunction();
    string name() const override;
    string description() const override;
    std::unique_ptr<ProblemBase> clone() const override;
};

class EggholderFunction : public BenchmarkFunctionBase {
  public:
    EggholderFunction();
    string name() const override;
    string description() const override;
    std::unique_ptr<ProblemBase> clone() const override;
};

class GramacyLeeFunction : public BenchmarkFunctionBase {
  public:
    GramacyLeeFunction();
    string name() const override;
    string description() const override;
    std::unique_ptr<ProblemBase> clone() const override;
};

class HolderTableFunction : public BenchmarkFunctionBase {
  public:
    HolderTableFunction();
    string name() const override;
    string description() const override;
    std::unique_ptr<ProblemBase> clone() const override;
};

class LangermannFunction : public BenchmarkFunctionBase {
  public:
    LangermannFunction();
    string name() const override;
    string description() const override;
    std::unique_ptr<ProblemBase> clone() const override;
};

class LevyFunction : public BenchmarkFunctionBase {
  public:
    LevyFunction();
    string name() const override;
    string description() const override;
    std::unique_ptr<ProblemBase> clone() const override;
};

class LevyN13Function : public BenchmarkFunctionBase {
  public:
    LevyN13Function();
    string name() const override;
    string description() const override;
    std::unique_ptr<ProblemBase> clone() const override;
};

class SchaefferN2Function : public BenchmarkFunctionBase {
  public:
    SchaefferN2Function();
    string name() const override;
    string description() const override;
    std::unique_ptr<ProblemBase> clone() const override;
};

class SchaefferN4Function : public BenchmarkFunctionBase {
  public:
    SchaefferN4Function();
    string name() const override;
    string description() const override;
    std::unique_ptr<ProblemBase> clone() const override;
};

class ShubertFunction : public BenchmarkFunctionBase {
  public:
    ShubertFunction();
    string name() const override;
    string description() const override;
    std::unique_ptr<ProblemBase> clone() const override;
};

class BohachevskyFunction : public BenchmarkFunctionBase {
  public:
    BohachevskyFunction();
    string name() const override;
    string description() const override;
    std::unique_ptr<ProblemBase> clone() const override;
};

class Perm0DBetaFunction : public BenchmarkFunctionBase {
  public:
    Perm0DBetaFunction();
    string name() const override;
    string description() const override;
    std::unique_ptr<ProblemBase> clone() const override;
};

class SumDifferentPowersFunction : public BenchmarkFunctionBase {
  public:
    SumDifferentPowersFunction();
    string name() const override;
    string description() const override;
    std::unique_ptr<ProblemBase> clone() const override;
};

class SumSquaresFunction : public BenchmarkFunctionBase {
  public:
    SumSquaresFunction();
    string name() const override;
    string description() const override;
    std::unique_ptr<ProblemBase> clone() const override;
};

class TridFunction : public BenchmarkFunctionBase {
  public:
    TridFunction();
    string name() const override;
    string description() const override;
    std::unique_ptr<ProblemBase> clone() const override;
};

class BoothFunction : public BenchmarkFunctionBase {
  public:
    BoothFunction();
    string name() const override;
    string description() const override;
    std::unique_ptr<ProblemBase> clone() const override;
};

class MatyasFunction : public BenchmarkFunctionBase {
  public:
    MatyasFunction();
    string name() const override;
    string description() const override;
    std::unique_ptr<ProblemBase> clone() const override;
};

class McCormickFunction : public BenchmarkFunctionBase {
  public:
    McCormickFunction();
    string name() const override;
    string description() const override;
    std::unique_ptr<ProblemBase> clone() const override;
};

class PowerSumFunction : public BenchmarkFunctionBase {
  public:
    PowerSumFunction();
    string name() const override;
    string description() const override;
    std::unique_ptr<ProblemBase> clone() const override;
};

class ZakharovFunction : public BenchmarkFunctionBase {
  public:
    ZakharovFunction();
    string name() const override;
    string description() const override;
    std::unique_ptr<ProblemBase> clone() const override;
};

class ThreeHumpCamelFunction : public BenchmarkFunctionBase {
  public:
    ThreeHumpCamelFunction();
    string name() const override;
    string description() const override;
    std::unique_ptr<ProblemBase> clone() const override;
};

class DixonPriceFunction : public BenchmarkFunctionBase {
  public:
    DixonPriceFunction();
    string name() const override;
    string description() const override;
    std::unique_ptr<ProblemBase> clone() const override;
};

class DeJongN5Function : public BenchmarkFunctionBase {
  public:
    DeJongN5Function();
    string name() const override;
    string description() const override;
    std::unique_ptr<ProblemBase> clone() const override;
};

class BealeFunction : public BenchmarkFunctionBase {
  public:
    BealeFunction();
    string name() const override;
    string description() const override;
    std::unique_ptr<ProblemBase> clone() const override;
};

class ColvilleFunction : public BenchmarkFunctionBase {
  public:
    ColvilleFunction();
    string name() const override;
    string description() const override;
    std::unique_ptr<ProblemBase> clone() const override;
};

class ForresterFunction : public BenchmarkFunctionBase {
  public:
    ForresterFunction();
    string name() const override;
    string description() const override;
    std::unique_ptr<ProblemBase> clone() const override;
};

class Hartmann3DFunction : public BenchmarkFunctionBase {
  public:
    Hartmann3DFunction();
    string name() const override;
    string description() const override;
    std::unique_ptr<ProblemBase> clone() const override;
};

class Hartmann4DFunction : public BenchmarkFunctionBase {
  public:
    Hartmann4DFunction();
    string name() const override;
    string description() const override;
    std::unique_ptr<ProblemBase> clone() const override;
};

class Hartmann6DFunction : public BenchmarkFunctionBase {
  public:
    Hartmann6DFunction();
    string name() const override;
    string description() const override;
    std::unique_ptr<ProblemBase> clone() const override;
};

class PermDBetaFunction : public BenchmarkFunctionBase {
  public:
    PermDBetaFunction();
    string name() const override;
    string description() const override;
    std::unique_ptr<ProblemBase> clone() const override;
};

class ShekelFunction : public BenchmarkFunctionBase {
  public:
    ShekelFunction();
    string name() const override;
    string description() const override;
    std::unique_ptr<ProblemBase> clone() const override;
};

class PowellFunction : public BenchmarkFunctionBase {
  public:
    PowellFunction();
    string name() const override;
    string description() const override;
    std::unique_ptr<ProblemBase> clone() const override;
};

class StyblinskiTangFunction : public BenchmarkFunctionBase {
  public:
    StyblinskiTangFunction();
    string name() const override;
    string description() const override;
    std::unique_ptr<ProblemBase> clone() const override;
};

#endif // BENCHMARK_FUNCTIONS_H
