#ifndef OPTIMIZER_HPP
#define OPTIMIZER_HPP

#include "benchmark/benchmark_functions.hpp"
#include "core/problem.hpp"
#include <cstdint>
#include <memory>
#include <vector>

class OptimizerInterface {
  public:
    virtual void run() = 0;
};

class OptimizerBase : public OptimizerInterface {
  public:
    OptimizerBase(uint32_t n_agents, uint32_t max_iterations, std::unique_ptr<ProblemBase> objective_function)
        : n_agents_(n_agents), max_iterations_(max_iterations),
          objective_function_(std::move(objective_function)), convergence_curve_(max_iterations) {}
    virtual ~OptimizerBase() = default;
    virtual void run() override = 0;
    virtual std::vector<std::tuple<std::vector<double>, double>> get_population_and_fitness() const = 0;
    virtual void migrate_and_run(const std::vector<std::vector<double>> &migrated_solutions) = 0;
    std::tuple<vector<double>, double> get_best_solution() const { return {best_solution_, best_fitness_}; }
    std::vector<double> get_convergence_curve() const { return convergence_curve_; }

  protected:
    uint32_t n_agents_;
    uint32_t max_iterations_;
    std::unique_ptr<ProblemBase> objective_function_;
    std::vector<double> convergence_curve_;
    std::vector<double> best_solution_;
    double best_fitness_;
};

#endif