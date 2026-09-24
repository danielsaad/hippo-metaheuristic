#include "problem.hpp"

double ProblemBase::evaluate(const std::vector<double> &x) const { return f_(x); }
const std::vector<double> &ProblemBase::lowerbound() const { return lowerbound_; }
const std::vector<double> &ProblemBase::upperbound() const { return upperbound_; }
void ProblemBase::set_f(const std::function<double(const std::vector<double> &)> &f) { f_ = f; }

std::unique_ptr<ProblemBase> ProblemBase::clone() const {
    auto new_problem = std::make_unique<ProblemBase>(*this);
    return new_problem;
}
