#include "benchmark/benchmark_functions.hpp"
#include "benchmark/benchmark_function_factory.hpp"
#include <cmath>
#include <numbers>
#include <stdexcept>

SphereFunction::SphereFunction() {
    n_dimensions_ = 30;
    lowerbound_ = vd(n_dimensions_, -100.0);
    upperbound_ = vd(n_dimensions_, 100.0);
    set_f([](const vd &x) {
        double sum = 0.0;
        for (double xi : x) {
            sum += xi * xi;
        }
        return sum;
    });
}

string
SphereFunction::name() const {
    return "Sphere Function";
}

string
SphereFunction::description() const {
    return "Sphere function";
}

std::unique_ptr<ProblemBase>
SphereFunction::clone() const {
    return std::make_unique<SphereFunction>(*this);
}

RosenbrockFunction::RosenbrockFunction() {
    n_dimensions_ = 5;
    lowerbound_ = vd(n_dimensions_, -30.0);
    upperbound_ = vd(n_dimensions_, 30.0);
    set_f([](const vd &x) {
        double sum = 0.0;
        for (size_t i = 0; i < x.size() - 1; i++) {
            double term1 = 100.0 * (x[i + 1] - x[i] * x[i]) * (x[i + 1] - x[i] * x[i]);
            double term2 = (1 - x[i]) * (1 - x[i]);
            sum += term1 + term2;
        }
        return sum;
    });
}

string
RosenbrockFunction::name() const {
    return "Rosenbrock Function";
}

string
RosenbrockFunction::description() const {
    return "Rosenbrock function";
}

std::unique_ptr<ProblemBase>
RosenbrockFunction::clone() const {
    return std::make_unique<RosenbrockFunction>(*this);
}

RastriginFunction::RastriginFunction() {
    n_dimensions_ = 30;
    lowerbound_ = vd(n_dimensions_, -5.12);
    upperbound_ = vd(n_dimensions_, 5.12);
    set_f([](const vd &x) {
        double sum = 10.0 * x.size();
        for (double xi : x) {
            sum += xi * xi - 10.0 * cos(2 * std::numbers::pi * xi);
        }
        return sum;
    });
}

string
RastriginFunction::name() const {
    return "Rastrigin Function";
}

string
RastriginFunction::description() const {
    return "Rastrigin function";
}

std::unique_ptr<ProblemBase>
RastriginFunction::clone() const {
    return std::make_unique<RastriginFunction>(*this);
}

GoldsteinPriceFunction::GoldsteinPriceFunction() {
    n_dimensions_ = 2;
    lowerbound_ = vd(n_dimensions_, -2.0);
    upperbound_ = vd(n_dimensions_, 2.0);
    set_f([](const vd &v) {
        double x = v[0];
        double y = v[1];
        double term1 =
            1 + pow(x + y + 1, 2) * (19 - 14 * x + 3 * pow(x, 2) - 14 * y + 6 * x * y + 3 * pow(y, 2));
        double term2 = 30 + pow(2 * x - 3 * y, 2) *
                                (18 - 32 * x + 12 * pow(x, 2) + 48 * y - 36 * x * y + 27 * pow(y, 2));
        return term1 * term2;
    });
}

string
GoldsteinPriceFunction::name() const {
    return "Goldstein-Price Function";
}

string
GoldsteinPriceFunction::description() const {
    return "Goldstein-Price function";
}

std::unique_ptr<ProblemBase>
GoldsteinPriceFunction::clone() const {
    return std::make_unique<GoldsteinPriceFunction>(*this);
}

SchwefelFunction::SchwefelFunction() {
    n_dimensions_ = 30;
    lowerbound_ = vd(n_dimensions_, -500.0);
    upperbound_ = vd(n_dimensions_, 500.0);
    set_f([](const vd &x) {
        double sum = 0.0;
        for (const auto xi : x) {
            sum += xi * sin(sqrt(fabs(xi)));
        }
        return 418.9829 * x.size() - sum;
    });
}

string
SchwefelFunction::name() const {
    return "Schwefel Function";
}

string
SchwefelFunction::description() const {
    return "Shifted Schwefel function, the 418.9829*d term is excluded";
}

std::unique_ptr<ProblemBase>
SchwefelFunction::clone() const {
    return std::make_unique<SchwefelFunction>(*this);
}

Schwefel222Function::Schwefel222Function() {
    n_dimensions_ = 30;
    lowerbound_ = vd(n_dimensions_, -100.0);
    upperbound_ = vd(n_dimensions_, 100.0);
    set_f([](const vd &x) {
        double sum = 0.0;
        for (double xi : x) {
            sum += pow(floor(xi + 0.5), 2);
        }
        return sum;
    });
}

string
Schwefel222Function::name() const {
    return "Schwefel's Problem 2.22 Function";
}

string
Schwefel222Function::description() const {
    return "Schwefel's Problem 2.22 function. It rounds each variable to the nearest integer.";
}

std::unique_ptr<ProblemBase>
Schwefel222Function::clone() const {
    return std::make_unique<Schwefel222Function>(*this);
}

EasonFunction::EasonFunction() {
    n_dimensions_ = 2;
    lowerbound_ = vd(n_dimensions_, -100.0);
    upperbound_ = vd(n_dimensions_, 100.0);
    set_f([](const vd &x) {
        return -cos(x[0]) * cos(x[1]) *
               exp(-(pow(x[0] - std::numbers::pi, 2) + pow(x[1] - std::numbers::pi, 2)));
    });
}

string
EasonFunction::name() const {
    return "Eason's Function";
}

string
EasonFunction::description() const {
    return "Eason's Function. Global minimum f(x)=-1 at (pi,pi). It is like a black-hole affecting the "
           "space-time, overall planar, but with a singularity at (pi,pi).";
}

std::unique_ptr<ProblemBase>
EasonFunction::clone() const {
    return std::make_unique<EasonFunction>(*this);
}

MichalewiczFunction::MichalewiczFunction() {
    n_dimensions_ = 10;
    lowerbound_ = vd(n_dimensions_, 0.0);
    upperbound_ = vd(n_dimensions_, std::numbers::pi);
    set_f([](const vd &x) {
        double sum = 0.0;
        double m = 10;
        double i = 1;
        for (const auto &xi : x) {
            sum += sin(xi) * pow(sin((i * xi * xi) / std::numbers::pi), 2 * m);
            i += 1;
        }
        return -sum;
    });
}

string
MichalewiczFunction::name() const {
    return "Michalewicz Function";
}

string
MichalewiczFunction::description() const {
    return "Michalewicz Function";
}

std::unique_ptr<ProblemBase>
MichalewiczFunction::clone() const {
    return std::make_unique<MichalewiczFunction>(*this);
}

HyperEllipsoidFunction::HyperEllipsoidFunction() {
    n_dimensions_ = 30;
    lowerbound_ = vd(n_dimensions_, -5.12);
    upperbound_ = vd(n_dimensions_, 5.12);
    set_f([](const vd &x) {
        double sum = 0.0;
        double i = 1;
        for (const auto &xi : x) {
            sum += (i * xi * xi);
            i += 1;
        }
        return sum;
    });
}

string
HyperEllipsoidFunction::name() const {
    return "Hyper-Ellipsoid Function";
}

string
HyperEllipsoidFunction::description() const {
    return "Hyper-Ellipsoid Function";
}

std::unique_ptr<ProblemBase>
HyperEllipsoidFunction::clone() const {
    return std::make_unique<HyperEllipsoidFunction>(*this);
}

RotatedHyperEllipsoidFunction::RotatedHyperEllipsoidFunction() {
    n_dimensions_ = 30;
    lowerbound_ = vd(n_dimensions_, -65.536);
    upperbound_ = vd(n_dimensions_, 65.536);
    set_f([](const vd &x) {
        double sum = 0.0;
        for (size_t i = 0; i < x.size(); i++) {
            double inner_sum = 0.0;
            for (size_t j = 0; j <= i; j++) {
                inner_sum += x[j] * x[j];
            }
            sum += inner_sum;
        }
        return sum;
    });
}

string
RotatedHyperEllipsoidFunction::name() const {
    return "Rotated Hyper-Ellipsoid Function";
}

string
RotatedHyperEllipsoidFunction::description() const {
    return "Rotated Hyper-Ellipsoid Function";
}

std::unique_ptr<ProblemBase>
RotatedHyperEllipsoidFunction::clone() const {
    return std::make_unique<RotatedHyperEllipsoidFunction>(*this);
}

AckleyFunction::AckleyFunction() {
    n_dimensions_ = 30;
    lowerbound_ = vd(n_dimensions_, -32.768);
    upperbound_ = vd(n_dimensions_, 32.768);
    set_f([](const vd &x) {
        double a = 20.0;
        double b = 0.2;
        double c = 2 * std::numbers::pi;
        double sum1 = 0.0;
        double sum2 = 0.0;
        for (double xi : x) {
            sum1 += xi * xi;
            sum2 += cos(c * xi);
        }
        double term1 = -a * exp(-b * sqrt(sum1 / x.size()));
        double term2 = -exp(sum2 / x.size());
        return term1 + term2 + a + exp(1);
    });
}

string
AckleyFunction::name() const {
    return "Ackley Function";
}

string
AckleyFunction::description() const {
    return "Ackley function";
}

std::unique_ptr<ProblemBase>
AckleyFunction::clone() const {
    return std::make_unique<AckleyFunction>(*this);
}

GriewankFunction::GriewankFunction() {
    n_dimensions_ = 30;
    lowerbound_ = vd(n_dimensions_, -600.0);
    upperbound_ = vd(n_dimensions_, 600.0);
    set_f([](const vd &x) {
        double sum = 0.0;
        double prod = 1.0;
        for (size_t i = 0; i < x.size(); i++) {
            sum += (x[i] * x[i]) / 4000.0;
            prod *= cos(x[i] / sqrt(i + 1));
        }
        return sum - prod + 1.0;
    });
}

string
GriewankFunction::name() const {
    return "Griewank Function";
}

string
GriewankFunction::description() const {
    return "Griewank function";
}

std::unique_ptr<ProblemBase>
GriewankFunction::clone() const {
    return std::make_unique<GriewankFunction>(*this);
}

BraninFunction::BraninFunction() {
    n_dimensions_ = 2;
    lowerbound_ = {-5, 0};
    upperbound_ = {10, 15};
    set_f([](const vd &x) {
        double a = 1.0;
        double b = 5.1 / (4 * std::numbers::pi * std::numbers::pi);
        double c = 5.0 / std::numbers::pi;
        double r = 6.0;
        double s = 10.0;
        double t = 1.0 / (8 * std::numbers::pi);
        return a * pow(x[1] - b * x[0] * x[0] + c * x[0] - r, 2) + s * (1 - t) * cos(x[0]) + s;
    });
}

string
BraninFunction::name() const {
    return "Branin Function";
}

string
BraninFunction::description() const {
    return "Branin function";
}

std::unique_ptr<ProblemBase>
BraninFunction::clone() const {
    return std::make_unique<BraninFunction>(*this);
}

SixHumpCamelFunction::SixHumpCamelFunction() {
    n_dimensions_ = 2;
    lowerbound_ = {-3, -2};
    upperbound_ = {3, 2};
    set_f([](const vd &x) {
        double x1 = x[0];
        double x2 = x[1];
        return (4 - 2.1 * x1 * x1 + (pow(x1, 4)) / 3) * x1 * x1 + x1 * x2 + (-4 + 4 * x2 * x2) * x2 * x2;
    });
}

string
SixHumpCamelFunction::name() const {
    return "Six-Hump Camel Function";
}

string
SixHumpCamelFunction::description() const {
    return "Six-Hump Camel function";
}

std::unique_ptr<ProblemBase>
SixHumpCamelFunction::clone() const {
    return std::make_unique<SixHumpCamelFunction>(*this);
}


BukinN6Function::BukinN6Function() {
    lowerbound_ = {-15, -3};
    upperbound_ = {-5, 3};
    n_dimensions_ = lowerbound_.size();
    set_f([](const vd &x) {
            return 100 * sqrt(fabs(x[1] - 0.01 * x[0] * x[0])) + 0.01 * fabs(x[0] + 10);
        });
}

string
BukinN6Function::name() const {
    return "Bukin N. 6 Function";
}

string
BukinN6Function::description() const {
    return "Bukin N. 6 Function";
}

std::unique_ptr<ProblemBase>
BukinN6Function::clone() const {
    return std::make_unique<BukinN6Function>(*this);
}

CrossInTrayFunction::CrossInTrayFunction() {
    n_dimensions_ = 2;
    lowerbound_ = vd(n_dimensions_, -10);
    upperbound_ = vd(n_dimensions_, 10);
    set_f([](const vd &x) {
            double e = exp(fabs(100 - sqrt(x[0] * x[0] + x[1] * x[1]) / std::numbers::pi));
            return -0.0001 * pow(fabs(sin(x[0]) * sin(x[1]) * e) + 1, 0.1);
        });
}

string
CrossInTrayFunction::name() const {
    return "Cross-in-Tray Function";
}

string
CrossInTrayFunction::description() const {
    return "Cross-in-Tray Function";
}

std::unique_ptr<ProblemBase>
CrossInTrayFunction::clone() const {
    return std::make_unique<CrossInTrayFunction>(*this);
}

DropWaveFunction::DropWaveFunction() {
    n_dimensions_ = 2;
    lowerbound_ = vd(n_dimensions_, -5.12);
    upperbound_ = vd(n_dimensions_, 5.12);
    set_f([](const vd &x) {
            double r = x[0] * x[0] + x[1] * x[1];
            return -(1 + cos(12 * sqrt(r))) / (0.5 * r + 2);
        });
}

string
DropWaveFunction::name() const {
    return "Drop-Wave Function";
}

string
DropWaveFunction::description() const {
    return "Drop-Wave Function";
}

std::unique_ptr<ProblemBase>
DropWaveFunction::clone() const {
    return std::make_unique<DropWaveFunction>(*this);
}

EggholderFunction::EggholderFunction() {
    n_dimensions_ = 2;
    lowerbound_ = vd(n_dimensions_, -512);
    upperbound_ = vd(n_dimensions_, 512);
    set_f([](const vd &x) {
            return -(x[1] + 47) * sin(sqrt(fabs(x[1] + x[0] / 2 + 47))) -
                   x[0] * sin(sqrt(fabs(x[0] - x[1] - 47)));
        });
}

string
EggholderFunction::name() const {
    return "Eggholder Function";
}

string
EggholderFunction::description() const {
    return "Eggholder Function";
}

std::unique_ptr<ProblemBase>
EggholderFunction::clone() const {
    return std::make_unique<EggholderFunction>(*this);
}

GramacyLeeFunction::GramacyLeeFunction() {
    n_dimensions_ = 1;
    lowerbound_ = vd(n_dimensions_, 0.5);
    upperbound_ = vd(n_dimensions_, 2.5);
    set_f([](const vd &x) { return sin(10 * std::numbers::pi * x[0]) / (2 * x[0]) + pow(x[0] - 1, 4); });
}

string
GramacyLeeFunction::name() const {
    return "Gramacy & Lee (2012) Function";
}

string
GramacyLeeFunction::description() const {
    return "Gramacy & Lee (2012) Function";
}

std::unique_ptr<ProblemBase>
GramacyLeeFunction::clone() const {
    return std::make_unique<GramacyLeeFunction>(*this);
}

HolderTableFunction::HolderTableFunction() {
    n_dimensions_ = 2;
    lowerbound_ = vd(n_dimensions_, -10);
    upperbound_ = vd(n_dimensions_, 10);
    set_f([](const vd &x) {
            return -fabs(sin(x[0]) * cos(x[1]) *
                         exp(fabs(1 - sqrt(x[0] * x[0] + x[1] * x[1]) / std::numbers::pi)));
        });
}

string
HolderTableFunction::name() const {
    return "Holder Table Function";
}

string
HolderTableFunction::description() const {
    return "Holder Table Function";
}

std::unique_ptr<ProblemBase>
HolderTableFunction::clone() const {
    return std::make_unique<HolderTableFunction>(*this);
}

LangermannFunction::LangermannFunction() {
    n_dimensions_ = 2;
    lowerbound_ = vd(n_dimensions_, 0);
    upperbound_ = vd(n_dimensions_, 10);
    set_f([](const vd &x) {
            const double c[] = {1, 2, 5, 2, 3};
            const double a[][2] = {{3, 5}, {5, 2}, {2, 1}, {1, 4}, {7, 9}};
            double sum = 0;
            for (int i = 0; i < 5; i++)
                sum += c[i] * exp(-(pow(x[0] - a[i][0], 2) + pow(x[1] - a[i][1], 2)) / std::numbers::pi) *
                       cos(std::numbers::pi * (pow(x[0] - a[i][0], 2) + pow(x[1] - a[i][1], 2)));
            return -sum;
        });
}

string
LangermannFunction::name() const {
    return "Langermann Function";
}

string
LangermannFunction::description() const {
    return "Langermann Function";
}

std::unique_ptr<ProblemBase>
LangermannFunction::clone() const {
    return std::make_unique<LangermannFunction>(*this);
}

LevyFunction::LevyFunction() {
    n_dimensions_ = 30;
    lowerbound_ = vd(n_dimensions_, -10);
    upperbound_ = vd(n_dimensions_, 10);
    set_f([](const vd &x) {
            auto w = [&](size_t i) { return 1 + (x[i] - 1) / 4; };
            double sum = sin(std::numbers::pi * w(0)) * sin(std::numbers::pi * w(0));
            for (size_t i = 0; i + 1 < x.size(); i++)
                sum += pow(w(i) - 1, 2) * (1 + 10 * pow(sin(std::numbers::pi * w(i) + 1), 2));
            return sum +
                   pow(w(x.size() - 1) - 1, 2) * (1 + pow(sin(2 * std::numbers::pi * w(x.size() - 1)), 2));
        });
}

string
LevyFunction::name() const {
    return "Levy Function";
}

string
LevyFunction::description() const {
    return "Levy Function";
}

std::unique_ptr<ProblemBase>
LevyFunction::clone() const {
    return std::make_unique<LevyFunction>(*this);
}

LevyN13Function::LevyN13Function() {
    n_dimensions_ = 2;
    lowerbound_ = vd(n_dimensions_, -10);
    upperbound_ = vd(n_dimensions_, 10);
    set_f([](const vd &x) {
            return pow(sin(3 * std::numbers::pi * x[0]), 2) +
                   pow(x[0] - 1, 2) * (1 + pow(sin(3 * std::numbers::pi * x[1]), 2)) +
                   pow(x[1] - 1, 2) * (1 + pow(sin(2 * std::numbers::pi * x[1]), 2));
        });
}

string
LevyN13Function::name() const {
    return "Levy Function N. 13";
}

string
LevyN13Function::description() const {
    return "Levy Function N. 13";
}

std::unique_ptr<ProblemBase>
LevyN13Function::clone() const {
    return std::make_unique<LevyN13Function>(*this);
}

SchaefferN2Function::SchaefferN2Function() {
    n_dimensions_ = 2;
    lowerbound_ = vd(n_dimensions_, -100);
    upperbound_ = vd(n_dimensions_, 100);
    set_f([](const vd &x) {
            double r = x[0] * x[0] + x[1] * x[1];
            double radius = sqrt(r);
            double value = pow(sin(radius), 2) - 0.5;
            return 0.5 + value / pow(1 + 0.001 * r, 2);
        });
}

string
SchaefferN2Function::name() const {
    return "Schaeffer Function N. 2";
}

string
SchaefferN2Function::description() const {
    return "Schaeffer Function N. 2";
}

std::unique_ptr<ProblemBase>
SchaefferN2Function::clone() const {
    return std::make_unique<SchaefferN2Function>(*this);
}

SchaefferN4Function::SchaefferN4Function() {
    n_dimensions_ = 2;
    lowerbound_ = vd(n_dimensions_, -100);
    upperbound_ = vd(n_dimensions_, 100);
    set_f([](const vd &x) {
            double r = x[0] * x[0] + x[1] * x[1];
            double radius = sqrt(r);
            double value = pow(sin(cos(radius)), 2) - 0.5;
            return 0.5 + value / pow(1 + 0.001 * r, 2);
        });
}

string
SchaefferN4Function::name() const {
    return "Schaeffer Function N. 4";
}

string
SchaefferN4Function::description() const {
    return "Schaeffer Function N. 4";
}

std::unique_ptr<ProblemBase>
SchaefferN4Function::clone() const {
    return std::make_unique<SchaefferN4Function>(*this);
}

ShubertFunction::ShubertFunction() {
    n_dimensions_ = 2;
    lowerbound_ = vd(n_dimensions_, -10);
    upperbound_ = vd(n_dimensions_, 10);
    set_f([](const vd &x) {
            double p[2]{};
            for (int d = 0; d < 2; d++)
                for (int i = 1; i <= 5; i++)
                    p[d] += i * cos((i + 1) * x[d] + i);
            return p[0] * p[1];
        });
}

string
ShubertFunction::name() const {
    return "Shubert Function";
}

string
ShubertFunction::description() const {
    return "Shubert Function";
}

std::unique_ptr<ProblemBase>
ShubertFunction::clone() const {
    return std::make_unique<ShubertFunction>(*this);
}

BohachevskyFunction::BohachevskyFunction() {
    n_dimensions_ = 2;
    lowerbound_ = vd(n_dimensions_, -100);
    upperbound_ = vd(n_dimensions_, 100);
    set_f([](const vd &x) {
            return x[0] * x[0] + 2 * x[1] * x[1] - 0.3 * cos(3 * std::numbers::pi * x[0]) -
                   0.4 * cos(4 * std::numbers::pi * x[1]) + 0.7;
        });
}

string
BohachevskyFunction::name() const {
    return "Bohachevsky Function";
}

string
BohachevskyFunction::description() const {
    return "Bohachevsky Function";
}

std::unique_ptr<ProblemBase>
BohachevskyFunction::clone() const {
    return std::make_unique<BohachevskyFunction>(*this);
}

Perm0DBetaFunction::Perm0DBetaFunction() {
    n_dimensions_ = 4;
    lowerbound_ = vd(n_dimensions_, -4);
    upperbound_ = vd(n_dimensions_, 4);
    set_f([](const vd &x) {
            const double beta = 10;
            double outer = 0;
            for (size_t i = 1; i <= x.size(); i++) {
                double inner = 0;
                for (size_t j = 1; j <= x.size(); j++) {
                    inner += (pow(j, i) + beta) * (pow(x[j - 1] / j, i) - 1.0);
                }
                outer += inner * inner;
            }
            return outer;
        });
}

string
Perm0DBetaFunction::name() const {
    return "Perm Function 0,d,beta";
}

string
Perm0DBetaFunction::description() const {
    return "Perm Function 0,d,beta";
}

std::unique_ptr<ProblemBase>
Perm0DBetaFunction::clone() const {
    return std::make_unique<Perm0DBetaFunction>(*this);
}

SumDifferentPowersFunction::SumDifferentPowersFunction() {
    n_dimensions_ = 30;
    lowerbound_ = vd(n_dimensions_, -1);
    upperbound_ = vd(n_dimensions_, 1);
    set_f([](const vd &x) {
            double s = 0;
            for (size_t i = 0; i < x.size(); i++)
                s += pow(fabs(x[i]), double(i + 2));
            return s;
        });
}

string
SumDifferentPowersFunction::name() const {
    return "Sum of Different Powers Function";
}

string
SumDifferentPowersFunction::description() const {
    return "Sum of Different Powers Function";
}

std::unique_ptr<ProblemBase>
SumDifferentPowersFunction::clone() const {
    return std::make_unique<SumDifferentPowersFunction>(*this);
}

SumSquaresFunction::SumSquaresFunction() {
    n_dimensions_ = 30;
    lowerbound_ = vd(n_dimensions_, -10);
    upperbound_ = vd(n_dimensions_, 10);
    set_f([](const vd &x) {
            double s = 0;
            for (size_t i = 0; i < x.size(); i++)
                s += (i + 1) * x[i] * x[i];
            return s;
        });
}

string
SumSquaresFunction::name() const {
    return "Sum Squares Function";
}

string
SumSquaresFunction::description() const {
    return "Sum Squares Function";
}

std::unique_ptr<ProblemBase>
SumSquaresFunction::clone() const {
    return std::make_unique<SumSquaresFunction>(*this);
}

TridFunction::TridFunction() {
    n_dimensions_ = 6;
    lowerbound_ = vd(n_dimensions_, -36);
    upperbound_ = vd(n_dimensions_, 36);
    set_f([](const vd &x) {
            double s = 0;
            for (double v : x)
                s += pow(v - 1, 2);
            for (size_t i = 1; i < x.size(); i++)
                s -= x[i] * x[i - 1];
            return s;
        });
}

string
TridFunction::name() const {
    return "Trid Function";
}

string
TridFunction::description() const {
    return "Trid Function";
}

std::unique_ptr<ProblemBase>
TridFunction::clone() const {
    return std::make_unique<TridFunction>(*this);
}

BoothFunction::BoothFunction() {
    n_dimensions_ = 2;
    lowerbound_ = vd(n_dimensions_, -10);
    upperbound_ = vd(n_dimensions_, 10);
    set_f([](const vd &x) { return pow(x[0] + 2 * x[1] - 7, 2) + pow(2 * x[0] + x[1] - 5, 2); });
}

string
BoothFunction::name() const {
    return "Booth Function";
}

string
BoothFunction::description() const {
    return "Booth Function";
}

std::unique_ptr<ProblemBase>
BoothFunction::clone() const {
    return std::make_unique<BoothFunction>(*this);
}

MatyasFunction::MatyasFunction() {
    n_dimensions_ = 2;
    lowerbound_ = vd(n_dimensions_, -10);
    upperbound_ = vd(n_dimensions_, 10);
    set_f([](const vd &x) { return 0.26 * (x[0] * x[0] + x[1] * x[1]) - 0.48 * x[0] * x[1]; });
}

string
MatyasFunction::name() const {
    return "Matyas Function";
}

string
MatyasFunction::description() const {
    return "Matyas Function";
}

std::unique_ptr<ProblemBase>
MatyasFunction::clone() const {
    return std::make_unique<MatyasFunction>(*this);
}

McCormickFunction::McCormickFunction() {
    lowerbound_ = {-1.5, -3};
    upperbound_ = {4, 4};
    n_dimensions_ = lowerbound_.size();
    set_f([](const vd &x) {
            return sin(x[0] + x[1]) + pow(x[0] - x[1], 2) - 1.5 * x[0] + 2.5 * x[1] + 1;
        });
}

string
McCormickFunction::name() const {
    return "McCormick Function";
}

string
McCormickFunction::description() const {
    return "McCormick Function";
}

std::unique_ptr<ProblemBase>
McCormickFunction::clone() const {
    return std::make_unique<McCormickFunction>(*this);
}

PowerSumFunction::PowerSumFunction() {
    n_dimensions_ = 4;
    lowerbound_ = vd(n_dimensions_, 0);
    upperbound_ = vd(n_dimensions_, 4);
    set_f([](const vd &x) {
            const double b[] = {8, 18, 44, 114};
            double s = 0;
            for (size_t k = 1; k <= 4; k++) {
                double t = 0;
                for (double v : x)
                    t += pow(v, double(k));
                s += pow(t - b[k - 1], 2);
            }
            return s;
        });
}

string
PowerSumFunction::name() const {
    return "Power Sum Function";
}

string
PowerSumFunction::description() const {
    return "Power Sum Function";
}

std::unique_ptr<ProblemBase>
PowerSumFunction::clone() const {
    return std::make_unique<PowerSumFunction>(*this);
}

ZakharovFunction::ZakharovFunction() {
    n_dimensions_ = 30;
    lowerbound_ = vd(n_dimensions_, -5);
    upperbound_ = vd(n_dimensions_, 10);
    set_f([](const vd &x) {
            double s = 0, w = 0;
            for (size_t i = 0; i < x.size(); i++) {
                s += x[i] * x[i];
                w += 0.5 * (i + 1) * x[i];
            }
            return s + w * w + pow(w, 4);
        });
}

string
ZakharovFunction::name() const {
    return "Zakharov Function";
}

string
ZakharovFunction::description() const {
    return "Zakharov Function";
}

std::unique_ptr<ProblemBase>
ZakharovFunction::clone() const {
    return std::make_unique<ZakharovFunction>(*this);
}

ThreeHumpCamelFunction::ThreeHumpCamelFunction() {
    n_dimensions_ = 2;
    lowerbound_ = vd(n_dimensions_, -5);
    upperbound_ = vd(n_dimensions_, 5);
    set_f([](const vd &x) {
            return 2 * x[0] * x[0] - 1.05 * pow(x[0], 4) + pow(x[0], 6) / 6 + x[0] * x[1] + x[1] * x[1];
        });
}

string
ThreeHumpCamelFunction::name() const {
    return "Three-Hump Camel Function";
}

string
ThreeHumpCamelFunction::description() const {
    return "Three-Hump Camel Function";
}

std::unique_ptr<ProblemBase>
ThreeHumpCamelFunction::clone() const {
    return std::make_unique<ThreeHumpCamelFunction>(*this);
}

DixonPriceFunction::DixonPriceFunction() {
    n_dimensions_ = 30;
    lowerbound_ = vd(n_dimensions_, -10);
    upperbound_ = vd(n_dimensions_, 10);
    set_f([](const vd &x) {
            double s = pow(x[0] - 1, 2);
            for (size_t i = 1; i < x.size(); i++)
                s += (i + 1) * pow(2 * x[i] * x[i] - x[i - 1], 2);
            return s;
        });
}

string
DixonPriceFunction::name() const {
    return "Dixon-Price Function";
}

string
DixonPriceFunction::description() const {
    return "Dixon-Price Function";
}

std::unique_ptr<ProblemBase>
DixonPriceFunction::clone() const {
    return std::make_unique<DixonPriceFunction>(*this);
}

DeJongN5Function::DeJongN5Function() {
    n_dimensions_ = 2;
    lowerbound_ = vd(n_dimensions_, -65.536);
    upperbound_ = vd(n_dimensions_, 65.536);
    set_f([](const vd &x) {
            double s = 0;
            for (int i = 0; i < 25; i++) {
                int a = i % 5 - 2, b = i / 5 - 2;
                s += 1.0 / (i + 1 + pow(x[0] - a, 6) + pow(x[1] - b, 6));
            }
            return 1.0 / (0.002 + s);
        });
}

string
DeJongN5Function::name() const {
    return "De Jong Function N. 5";
}

string
DeJongN5Function::description() const {
    return "De Jong Function N. 5";
}

std::unique_ptr<ProblemBase>
DeJongN5Function::clone() const {
    return std::make_unique<DeJongN5Function>(*this);
}

BealeFunction::BealeFunction() {
    n_dimensions_ = 2;
    lowerbound_ = vd(n_dimensions_, -4.5);
    upperbound_ = vd(n_dimensions_, 4.5);
    set_f([](const vd &x) {
            return pow(1.5 - x[0] + x[0] * x[1], 2) + pow(2.25 - x[0] + x[0] * x[1] * x[1], 2) +
                   pow(2.625 - x[0] + x[0] * pow(x[1], 3), 2);
        });
}

string
BealeFunction::name() const {
    return "Beale Function";
}

string
BealeFunction::description() const {
    return "Beale Function";
}

std::unique_ptr<ProblemBase>
BealeFunction::clone() const {
    return std::make_unique<BealeFunction>(*this);
}

ColvilleFunction::ColvilleFunction() {
    n_dimensions_ = 4;
    lowerbound_ = vd(n_dimensions_, -10);
    upperbound_ = vd(n_dimensions_, 10);
    set_f([](const vd &x) {
            return 100 * pow(x[0] * x[0] - x[1], 2) + pow(x[0] - 1, 2) + pow(x[2] - 1, 2) +
                   90 * pow(x[2] * x[2] - x[3], 2) + 10.1 * (pow(x[1] - 1, 2) + pow(x[3] - 1, 2)) +
                   19.8 * (x[1] - 1) * (x[3] - 1);
        });
}

string
ColvilleFunction::name() const {
    return "Colville Function";
}

string
ColvilleFunction::description() const {
    return "Colville Function";
}

std::unique_ptr<ProblemBase>
ColvilleFunction::clone() const {
    return std::make_unique<ColvilleFunction>(*this);
}

ForresterFunction::ForresterFunction() {
    n_dimensions_ = 1;
    lowerbound_ = vd(n_dimensions_, 0);
    upperbound_ = vd(n_dimensions_, 1);
    set_f([](const vd &x) { return pow(6 * x[0] - 2, 2) * sin(12 * x[0] - 4); });
}

string
ForresterFunction::name() const {
    return "Forrester et al. (2008) Function";
}

string
ForresterFunction::description() const {
    return "Forrester et al. (2008) Function";
}

std::unique_ptr<ProblemBase>
ForresterFunction::clone() const {
    return std::make_unique<ForresterFunction>(*this);
}

Hartmann3DFunction::Hartmann3DFunction() {
    constexpr size_t dimensions = 3;
    constexpr double a[4][6] = {{10, 3, 17, 3.5, 1.7, 8},
                                  {0.05, 10, 17, 0.1, 8, 14},
                                  {3, 3.5, 1.7, 10, 17, 8},
                                  {17, 8, 0.05, 10, 0.1, 14}};
    constexpr double p[4][6] = {{0.1312, 0.1696, 0.5569, 0.0124, 0.8283, 0.5886},
                                  {0.2329, 0.4135, 0.8307, 0.3736, 0.1004, 0.9991},
                                  {0.2348, 0.1451, 0.3522, 0.2883, 0.3047, 0.6650},
                                  {0.4047, 0.8828, 0.8732, 0.5743, 0.1091, 0.0381}};
    constexpr double c[] = {1, 1.2, 3, 3.2};
    n_dimensions_ = dimensions;
    lowerbound_ = vd(dimensions, 0);
    upperbound_ = vd(dimensions, 1);
    set_f([=](const vd &x) {
        double sum = 0;
        for (size_t i = 0; i < 4; ++i) {
            double exponent = 0;
            for (size_t j = 0; j < dimensions; ++j) exponent += a[i][j] * pow(x[j] - p[i][j], 2);
            sum += c[i] * exp(-exponent);
        }
        return -sum;
    });
}
string
Hartmann3DFunction::name() const {
    return "Hartmann 3-D Function";
}

string
Hartmann3DFunction::description() const {
    return "Hartmann 3-D Function";
}

std::unique_ptr<ProblemBase>
Hartmann3DFunction::clone() const {
    return std::make_unique<Hartmann3DFunction>(*this);
}

Hartmann4DFunction::Hartmann4DFunction() {
    constexpr size_t dimensions = 4;
    constexpr double a[4][6] = {{10, 3, 17, 3.5, 1.7, 8},
                                  {0.05, 10, 17, 0.1, 8, 14},
                                  {3, 3.5, 1.7, 10, 17, 8},
                                  {17, 8, 0.05, 10, 0.1, 14}};
    constexpr double p[4][6] = {{0.1312, 0.1696, 0.5569, 0.0124, 0.8283, 0.5886},
                                  {0.2329, 0.4135, 0.8307, 0.3736, 0.1004, 0.9991},
                                  {0.2348, 0.1451, 0.3522, 0.2883, 0.3047, 0.6650},
                                  {0.4047, 0.8828, 0.8732, 0.5743, 0.1091, 0.0381}};
    constexpr double c[] = {1, 1.2, 3, 3.2};
    n_dimensions_ = dimensions;
    lowerbound_ = vd(dimensions, 0);
    upperbound_ = vd(dimensions, 1);
    set_f([=](const vd &x) {
        double sum = 0;
        for (size_t i = 0; i < 4; ++i) {
            double exponent = 0;
            for (size_t j = 0; j < dimensions; ++j) exponent += a[i][j] * pow(x[j] - p[i][j], 2);
            sum += c[i] * exp(-exponent);
        }
        return -sum;
    });
}
string
Hartmann4DFunction::name() const {
    return "Hartmann 4-D Function";
}

string
Hartmann4DFunction::description() const {
    return "Hartmann 4-D Function";
}

std::unique_ptr<ProblemBase>
Hartmann4DFunction::clone() const {
    return std::make_unique<Hartmann4DFunction>(*this);
}

Hartmann6DFunction::Hartmann6DFunction() {
    constexpr size_t dimensions = 6;
    constexpr double a[4][6] = {{10, 3, 17, 3.5, 1.7, 8},
                                  {0.05, 10, 17, 0.1, 8, 14},
                                  {3, 3.5, 1.7, 10, 17, 8},
                                  {17, 8, 0.05, 10, 0.1, 14}};
    constexpr double p[4][6] = {{0.1312, 0.1696, 0.5569, 0.0124, 0.8283, 0.5886},
                                  {0.2329, 0.4135, 0.8307, 0.3736, 0.1004, 0.9991},
                                  {0.2348, 0.1451, 0.3522, 0.2883, 0.3047, 0.6650},
                                  {0.4047, 0.8828, 0.8732, 0.5743, 0.1091, 0.0381}};
    constexpr double c[] = {1, 1.2, 3, 3.2};
    n_dimensions_ = dimensions;
    lowerbound_ = vd(dimensions, 0);
    upperbound_ = vd(dimensions, 1);
    set_f([=](const vd &x) {
        double sum = 0;
        for (size_t i = 0; i < 4; ++i) {
            double exponent = 0;
            for (size_t j = 0; j < dimensions; ++j) exponent += a[i][j] * pow(x[j] - p[i][j], 2);
            sum += c[i] * exp(-exponent);
        }
        return -sum;
    });
}
string
Hartmann6DFunction::name() const {
    return "Hartmann 6-D Function";
}

string
Hartmann6DFunction::description() const {
    return "Hartmann 6-D Function";
}

std::unique_ptr<ProblemBase>
Hartmann6DFunction::clone() const {
    return std::make_unique<Hartmann6DFunction>(*this);
}

PermDBetaFunction::PermDBetaFunction() {
    n_dimensions_ = 4;
    lowerbound_ = vd(n_dimensions_, -4);
    upperbound_ = vd(n_dimensions_, 4);
    set_f([](const vd &x) {
            const double beta = 10;
            double outer = 0;
            for (size_t i = 1; i <= x.size(); i++) {
                double inner = 0;
                for (size_t j = 1; j <= x.size(); j++) {
                    inner += (j + beta) * (pow(x[j - 1], i) - pow(1.0 / j, i));
                }
                outer += inner * inner;
            }
            return outer;
        });
}

string
PermDBetaFunction::name() const {
    return "Perm Function d,beta";
}

string
PermDBetaFunction::description() const {
    return "Perm Function d,beta";
}

std::unique_ptr<ProblemBase>
PermDBetaFunction::clone() const {
    return std::make_unique<PermDBetaFunction>(*this);
}

ShekelFunction::ShekelFunction() {
    n_dimensions_ = 4;
    lowerbound_ = vd(n_dimensions_, 0);
    upperbound_ = vd(n_dimensions_, 10);
    set_f([](const vd &x) {
            const double a[10][4] = {{4, 4, 4, 4}, {1, 1, 1, 1},    {8, 8, 8, 8}, {6, 6, 6, 6},
                                     {3, 7, 3, 7}, {2, 9, 2, 9},    {5, 5, 3, 3}, {8, 1, 8, 1},
                                     {6, 2, 6, 2}, {7, 3.6, 7, 3.6}};
            const double c[] = {0.1, 0.2, 0.2, 0.4, 0.4, 0.6, 0.3, 0.7, 0.5, 0.5};
            double s = 0;
            for (int i = 0; i < 10; i++) {
                double q = c[i];
                for (int j = 0; j < 4; j++)
                    q += pow(x[j] - a[i][j], 2);
                s -= 1 / q;
            }
            return s;
        });
}

string
ShekelFunction::name() const {
    return "Shekel Function";
}

string
ShekelFunction::description() const {
    return "Shekel Function";
}

std::unique_ptr<ProblemBase>
ShekelFunction::clone() const {
    return std::make_unique<ShekelFunction>(*this);
}

PowellFunction::PowellFunction() {
    n_dimensions_ = 4;
    lowerbound_ = vd(n_dimensions_, -4);
    upperbound_ = vd(n_dimensions_, 5);
    set_f([](const vd &x) {
            return pow(x[0] + 10 * x[1], 2) + 5 * pow(x[2] - x[3], 2) + pow(x[1] - 2 * x[2], 4) +
                   10 * pow(x[0] - x[3], 4);
        });
}

string
PowellFunction::name() const {
    return "Powell Function";
}

string
PowellFunction::description() const {
    return "Powell Function";
}

std::unique_ptr<ProblemBase>
PowellFunction::clone() const {
    return std::make_unique<PowellFunction>(*this);
}

StyblinskiTangFunction::StyblinskiTangFunction() {
    n_dimensions_ = 30;
    lowerbound_ = vd(n_dimensions_, -5);
    upperbound_ = vd(n_dimensions_, 5);
    set_f([](const vd &x) {
            double s = 0;
            for (double v : x)
                s += pow(v, 4) - 16 * v * v + 5 * v;
            return s / 2;
        });
}

string
StyblinskiTangFunction::name() const {
    return "Styblinski-Tang Function";
}

string
StyblinskiTangFunction::description() const {
    return "Styblinski-Tang Function";
}

std::unique_ptr<ProblemBase>
StyblinskiTangFunction::clone() const {
    return std::make_unique<StyblinskiTangFunction>(*this);
}
