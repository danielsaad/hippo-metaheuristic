#include "benchmark_functions.h"
#include <cmath>
#include <string>

using std::string;

sphere_function::sphere_function() {
    n_dimensions = 30;
    lowerbound = vd(n_dimensions, -100.0);
    upperbound = vd(n_dimensions, 100.0);
    set_f();
}

std::string sphere_function::name() const { return "Sphere Function"; }

std::string sphere_function::description() const { return "Sphere function"; }

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
            sum += xi * sin(sqrt(fabs(xi)));
        }
        return -sum;
    };
}
