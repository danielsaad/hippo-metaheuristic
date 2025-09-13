#include "benchmark_functions.h"
#include <cmath>
#include <string>

sphere_function::sphere_function() {
    n_dimensions = 30;
    lowerbound = vd(n_dimensions, -100.0);
    upperbound = vd(n_dimensions, 100.0);
    set_f();
}

string sphere_function::name() const { return "Sphere Function"; }

string sphere_function::description() const { return "Sphere function"; }

void sphere_function::set_f() {
    f = [](const vd &x) {
        double sum = 0.0;
        for (double xi : x) {
            sum += xi * xi;
        }
        return sum;
    };
}

rosenbrock_function::rosenbrock_function() {
    n_dimensions = 5;
    lowerbound = vd(n_dimensions, -30.0);
    upperbound = vd(n_dimensions, 30.0);
    set_f();
}

string rosenbrock_function::name() const { return "Rosenbrock Function"; }

string rosenbrock_function::description() const { return "Rosenbrock function"; }

void rosenbrock_function::set_f() {
    f = [](const vd &x) {
        double sum = 0.0;
        for (size_t i = 0; i < x.size() - 1; i++) {
            double term1 = 100.0 * (x[i + 1] - x[i] * x[i]) * (x[i + 1] - x[i] * x[i]);
            double term2 = (1 - x[i]) * (1 - x[i]);
            sum += term1 + term2;
        }
        return sum;
    };
}

rastrigin_function::rastrigin_function() {
    n_dimensions = 30;
    lowerbound = vd(n_dimensions, -5.12);
    upperbound = vd(n_dimensions, 5.12);
    set_f();
}

string rastrigin_function::name() const { return "Rastrigin Function"; }

string rastrigin_function::description() const { return "Rastrigin function"; }

void rastrigin_function::set_f() {
    f = [](const vd &x) {
        double sum = 10.0 * x.size();
        for (double xi : x) {
            sum += xi * xi - 10.0 * cos(2 * std::numbers::pi * xi);
        }
        return sum;
    };
}

goldstein_price_function::goldstein_price_function() {
    n_dimensions = 2;
    lowerbound = vd(n_dimensions, -2.0);
    upperbound = vd(n_dimensions, 2.0);
    set_f();
}

string goldstein_price_function::name() const { return "Goldstein-Price Function"; }

string goldstein_price_function::description() const { return "Goldstein-Price function"; }

void goldstein_price_function::set_f() {
    f = [](const vd &v) {
        double x = v[0];
        double y = v[1];
        double term1 =
            1 + pow(x + y + 1, 2) * (19 - 14 * x + 3 * pow(x, 2) - 14 * y + 6 * x * y + 3 * pow(y, 2));
        double term2 = 30 + pow(2 * x - 3 * y, 2) *
                                (18 - 32 * x + 12 * pow(x, 2) + 48 * y - 36 * x * y + 27 * pow(y, 2));
        return term1 * term2;
    };
}

schwefel_function::schwefel_function() {
    n_dimensions = 30;
    lowerbound = vd(n_dimensions, -500.0);
    upperbound = vd(n_dimensions, 500.0);
    set_f();
}

string schwefel_function::name() const { return "Schwefel Function"; }

string schwefel_function::description() const {
    return "Shifted Schwefel function, the 418.9829*d term is excluded";
}

void schwefel_function::set_f() {
    f = [](const vd &x) {
        double sum = 0.0;
        for (double xi : x) {
            sum += -xi * sin(sqrt(fabs(xi)));
        }
        return sum;
    };
}

schwefel_222_function::schwefel_222_function() {
    n_dimensions = 30;
    lowerbound = vd(n_dimensions, -100.0);
    upperbound = vd(n_dimensions, 100.0);
    set_f();
}

string schwefel_222_function::name() const { return "Schwefel's Problem 2.22 Function"; }

string schwefel_222_function::description() const {
    return "Schwefel's Problem 2.22 function. It rounds each variable to the nearest integer.";
}

void schwefel_222_function::set_f() {
    f = [](const vd &x) {
        double sum = 0.0;
        for (double xi : x) {
            sum += pow(floor(xi + 0.5), 2);
        }
        return sum;
    };
}

eason_function::eason_function() {
    n_dimensions = 2;
    lowerbound = vd(n_dimensions, -100.0);
    upperbound = vd(n_dimensions, 100.0);
    set_f();
}

string eason_function::name() const { return "Eason's Function"; }

string eason_function::description() const {
    return "Eason's Function. Global minimum f(x)=-1 at (pi,pi). It is like a black-hole affecting the "
           "space-time, overall planar, but with a singularity at (pi,pi).";
}

void eason_function::set_f() {
    f = [](const vd &x) {
        return -cos(x[0]) * cos(x[1]) *
               exp(-(pow(x[0] - std::numbers::pi, 2) + pow(x[1] - std::numbers::pi, 2)));
    };
}

michalewicz_function::michalewicz_function() {
    n_dimensions = 10;
    lowerbound = vd(n_dimensions, 0.0);
    upperbound = vd(n_dimensions, std::numbers::pi);
    set_f();
}

string michalewicz_function::name() const { return "Michalewicz Function"; }

string michalewicz_function::description() const { return "Michalewicz Function"; }

void michalewicz_function::set_f() {
    f = [](const vd &x) {
        double sum = 0.0;
        double m = 10;
        double i = 1;
        for (const auto &xi : x) {
            sum += sin(xi) * pow(sin((i * xi * xi) / std::numbers::pi), 2 * m);
            i += 1;
        }
        return -sum;
    };
}

hyper_ellipsoid_function::hyper_ellipsoid_function() {
    n_dimensions = 30;
    lowerbound = vd(n_dimensions, -5.12);
    upperbound = vd(n_dimensions, 5.12);
    set_f();
}

string hyper_ellipsoid_function::name() const { return "Hyper-Ellipsoid Function"; }

string hyper_ellipsoid_function::description() const { return "Hyper-Ellipsoid Function"; }

void hyper_ellipsoid_function::set_f() {
    f = [](const vd &x) {
        double sum = 0.0;
        double i = 1;
        for (const auto &xi : x) {
            sum += (i * xi * xi);
            i += 1;
        }
        return sum;
    };
}

rotated_hyper_ellipsoid_function::rotated_hyper_ellipsoid_function() {
    n_dimensions = 30;
    lowerbound = vd(n_dimensions, -65.536);
    upperbound = vd(n_dimensions, 65.536);
    set_f();
}

string rotated_hyper_ellipsoid_function::name() const { return "Rotated Hyper-Ellipsoid Function"; }

string rotated_hyper_ellipsoid_function::description() const { return "Rotated Hyper-Ellipsoid Function"; }

void rotated_hyper_ellipsoid_function::set_f() {
    f = [](const vd &x) {
        double sum = 0.0;
        for (size_t i = 0; i < x.size(); i++) {
            double inner_sum = 0.0;
            for (size_t j = 0; j <= i; j++) {
                inner_sum += x[j] * x[j];
            }
            sum += inner_sum;
        }
        return sum;
    };
}

ackley_function::ackley_function() {
    n_dimensions = 30;
    lowerbound = vd(n_dimensions, -32.768);
    upperbound = vd(n_dimensions, 32.768);
    set_f();
}

string ackley_function::name() const { return "Ackley Function"; }

string ackley_function::description() const { return "Ackley function"; }

void ackley_function::set_f() {
    f = [](const vd &x) {
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
    };
}

griewank_function::griewank_function() {
    n_dimensions = 30;
    lowerbound = vd(n_dimensions, -600.0);
    upperbound = vd(n_dimensions, 600.0);
    set_f();
}

string griewank_function::name() const { return "Griewank Function"; }
string griewank_function::description() const { return "Griewank function"; }

void griewank_function::set_f() {
    f = [](const vd &x) {
        double sum = 0.0;
        double prod = 1.0;
        for (size_t i = 0; i < x.size(); i++) {
            sum += (x[i] * x[i]) / 4000.0;
            prod *= cos(x[i] / sqrt(i + 1));
        }
        return sum - prod + 1.0;
    };
}

branin_function::branin_function() {
    n_dimensions = 2;
    lowerbound = {-5, 0};
    upperbound = {10, 15};
    set_f();
}

string branin_function::name() const { return "Branin Function"; }

string branin_function::description() const { return "Branin function"; }

void branin_function::set_f() {
    f = [](const vd &x) {
        double a = 1.0;
        double b = 5.1 / (4 * std::numbers::pi * std::numbers::pi);
        double c = 5.0 / std::numbers::pi;
        double r = 6.0;
        double s = 10.0;
        double t = 1.0 / (8 * std::numbers::pi);
        return a * pow(x[1] - b * x[0] * x[0] + c * x[0] - r, 2) + s * (1 - t) * cos(x[0]) + s;
    };
}

six_hump_camel_function::six_hump_camel_function() {
    n_dimensions = 2;
    lowerbound = {-3, -2};
    upperbound = {3, 2};
    set_f();
}

string six_hump_camel_function::name() const { return "Six-Hump Camel Function"; }

string six_hump_camel_function::description() const { return "Six-Hump Camel function"; }

void six_hump_camel_function::set_f() {
    f = [](const vd &x) {
        double x1 = x[0];
        double x2 = x[1];
        return (4 - 2.1 * x1 * x1 + (pow(x1, 4)) / 3) * x1 * x1 + x1 * x2 + (-4 + 4 * x2 * x2) * x2 * x2;
    };
}