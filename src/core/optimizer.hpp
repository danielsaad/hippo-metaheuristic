#ifndef OPTIMIZER_HPP
#define OPTIMIZER_HPP

#include "benchmark/benchmark_functions.hpp"
#include "core/problem.hpp"
#include <cstdint>
#include <limits>
#include <memory>
#include <vector>

class OptimizerInterface {
  public:
    virtual void
    run(bool initialize = true) = 0;
    virtual void
    set_population_with_fitness(const std::vector<std::vector<double>> &population,
                                const std::vector<double> &fitness) = 0;
    virtual std::tuple<std::vector<std::vector<double>>, std::vector<double>>
    get_population_and_fitness() const = 0;
    virtual ~OptimizerInterface() = default;
};

class OptimizerBase : public OptimizerInterface {
  public:
    OptimizerBase(uint32_t n_agents, uint32_t max_iterations, std::unique_ptr<ProblemBase> objective_function)
        : n_agents_(n_agents), max_iterations_(max_iterations),
          objective_function_(std::move(objective_function)), convergence_curve_(max_iterations),
          best_fitness_(std::numeric_limits<double>::infinity()) {}

    virtual ~OptimizerBase() = default;

    virtual int
    get_optimizer_id() const = 0;

    std::tuple<std::vector<double>, double>
    get_best_solution() const {
        return {best_solution_, best_fitness_};
    }

    void
    update_best_solution(const std::vector<double> &solution, double fitness) {
        if (fitness < best_fitness_) {
            best_solution_ = solution;
            best_fitness_ = fitness;
        }
    }

    virtual std::unique_ptr<OptimizerBase>
    clone() = 0;

    std::vector<double>
    get_convergence_curve() const {
        return convergence_curve_;
    }

  protected:
    uint32_t n_agents_;
    uint32_t max_iterations_;
    std::unique_ptr<ProblemBase> objective_function_;
    std::vector<double> convergence_curve_;
    std::vector<double> best_solution_;
    double best_fitness_;
};

#endif
