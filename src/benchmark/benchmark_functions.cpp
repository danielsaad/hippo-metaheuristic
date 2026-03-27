#include "benchmark/benchmark_functions.hpp"
#include <cmath>
#include <string>

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

string SphereFunction::name() const { return "Sphere Function"; }

string SphereFunction::description() const { return "Sphere function"; }

std::unique_ptr<ProblemBase> SphereFunction::clone() const { return std::make_unique<SphereFunction>(*this); }

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

string RosenbrockFunction::name() const { return "Rosenbrock Function"; }

string RosenbrockFunction::description() const { return "Rosenbrock function"; }

std::unique_ptr<ProblemBase> RosenbrockFunction::clone() const {
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

string RastriginFunction::name() const { return "Rastrigin Function"; }

string RastriginFunction::description() const { return "Rastrigin function"; }

std::unique_ptr<ProblemBase> RastriginFunction::clone() const {
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

string GoldsteinPriceFunction::name() const { return "Goldstein-Price Function"; }

string GoldsteinPriceFunction::description() const { return "Goldstein-Price function"; }

std::unique_ptr<ProblemBase> GoldsteinPriceFunction::clone() const {
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

string SchwefelFunction::name() const { return "Schwefel Function"; }

string SchwefelFunction::description() const {
    return "Shifted Schwefel function, the 418.9829*d term is excluded";
}

std::unique_ptr<ProblemBase> SchwefelFunction::clone() const {
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

string Schwefel222Function::name() const { return "Schwefel's Problem 2.22 Function"; }

string Schwefel222Function::description() const {
    return "Schwefel's Problem 2.22 function. It rounds each variable to the nearest integer.";
}

std::unique_ptr<ProblemBase> Schwefel222Function::clone() const {
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

string EasonFunction::name() const { return "Eason's Function"; }

string EasonFunction::description() const {
    return "Eason's Function. Global minimum f(x)=-1 at (pi,pi). It is like a black-hole affecting the "
           "space-time, overall planar, but with a singularity at (pi,pi).";
}

std::unique_ptr<ProblemBase> EasonFunction::clone() const { return std::make_unique<EasonFunction>(*this); }

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

string MichalewiczFunction::name() const { return "Michalewicz Function"; }

string MichalewiczFunction::description() const { return "Michalewicz Function"; }

std::unique_ptr<ProblemBase> MichalewiczFunction::clone() const {
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

string HyperEllipsoidFunction::name() const { return "Hyper-Ellipsoid Function"; }

string HyperEllipsoidFunction::description() const { return "Hyper-Ellipsoid Function"; }

std::unique_ptr<ProblemBase> HyperEllipsoidFunction::clone() const {
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

string RotatedHyperEllipsoidFunction::name() const { return "Rotated Hyper-Ellipsoid Function"; }

string RotatedHyperEllipsoidFunction::description() const { return "Rotated Hyper-Ellipsoid Function"; }

std::unique_ptr<ProblemBase> RotatedHyperEllipsoidFunction::clone() const {
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

string AckleyFunction::name() const { return "Ackley Function"; }

string AckleyFunction::description() const { return "Ackley function"; }

std::unique_ptr<ProblemBase> AckleyFunction::clone() const { return std::make_unique<AckleyFunction>(*this); }

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

string GriewankFunction::name() const { return "Griewank Function"; }
string GriewankFunction::description() const { return "Griewank function"; }

std::unique_ptr<ProblemBase> GriewankFunction::clone() const {
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

string BraninFunction::name() const { return "Branin Function"; }

string BraninFunction::description() const { return "Branin function"; }

std::unique_ptr<ProblemBase> BraninFunction::clone() const { return std::make_unique<BraninFunction>(*this); }

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

string SixHumpCamelFunction::name() const { return "Six-Hump Camel Function"; }

string SixHumpCamelFunction::description() const { return "Six-Hump Camel function"; }

std::unique_ptr<ProblemBase> SixHumpCamelFunction::clone() const {
    return std::make_unique<SixHumpCamelFunction>(*this);
}
