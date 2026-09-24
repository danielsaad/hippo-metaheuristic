#ifndef PROBLEM_HPP
#define PROBLEM_HPP
#include <cstdint>
#include <functional>
#include <memory>
#include <vector>

class ProblemBase {
  public:
    ProblemBase() : n_dimensions_(0), lowerbound_(), upperbound_(), f_(nullptr) {}
    virtual ~ProblemBase() = default;
    void set_f(const std::function<double(const std::vector<double> &)> &f);
    double evaluate(const std::vector<double> &x) const;
    uint32_t n_dimensions() const { return n_dimensions_; }
    const std::vector<double> &lowerbound() const;
    const std::vector<double> &upperbound() const;
    virtual std::unique_ptr<ProblemBase> clone() const;

  protected:
    uint32_t n_dimensions_;
    std::vector<double> lowerbound_;
    std::vector<double> upperbound_;
    std::function<double(const std::vector<double> &)> f_;
};

#endif
