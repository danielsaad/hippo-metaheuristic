
#ifndef HIPPO_OPTIMIZER_H
#define HIPPO_OPTIMIZER_H

#include "core/optimizer.hpp"
#include "ho/function.hpp"
#include "ho/hippo_math.hpp"
#include "ho/hippo_random.hpp"
#include <algorithm>
#include <cstdint>
#include <iostream>
#include <random>

class HippoOptimizer : public OptimizerBase {
    using OptimizerBase::OptimizerBase; // Inherit constructors
  public:
    HippoOptimizer(uint32_t n_hippo, uint32_t max_iterations,
                   std::unique_ptr<ProblemBase> objective_function);

    void run() override;
    void migrate_and_run(const std::vector<std::vector<double>> &migrated_solutions) override;
    std::vector<std::tuple<std::vector<double>, double>> get_population_and_fitness() const override;

  private:
    // initial parameters
    uint32_t n_hippo;
    uint32_t max_iterations;
    double lowerbound_;
    double upperbound_;
    uint32_t n_dimensions_;
    std::function<double(const vector<double> &)> fitness_function;

    // data structures
    vector<double> fitness_vector;
    vector<double> lowerbound_vector;  // solution's lowerbound
    vector<double> upperbound_vector;  // solution's upperbound
    vector<vector<double>> population; // population of hippos

    void initialize();
    void initialize(const vector<std::vector<double>>& migrated_solutions);
    void explore(uint32_t best_idx, uint32_t iteration);
    void defend();
    void escape(uint32_t iteration);
};

#endif // HIPPO_OPTIMIZER_H