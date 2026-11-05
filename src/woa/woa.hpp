#ifndef WOA_HPP
#define WOA_HPP

#include "core/optimizer.hpp"
#include "core/optimizer_factory.hpp"
#include "core/problem.hpp"
#include "random/random_gen.hpp"
#include <iostream>
#include <numbers>
#include <print>
#include <random>
#include <vector>

class Woa : public OptimizerBase {
  public:
    Woa(uint32_t n_agents, uint32_t max_it, std::unique_ptr<ProblemBase> objective_function)
        : OptimizerBase(n_agents, max_it, std::move(objective_function)) {
        configure();
        std::print(
            "Initialized WOA with {} agents, max iterations: {}, lower bound: {}, upper bound: {} on a "
            "{}-dimensional problem\n",
            n_agents_, max_iterations_, lower_bound_, upper_bound_, objective_function_->n_dimensions());
        std::cout.flush();
    }

    std::tuple<std::vector<std::vector<double>>, std::vector<double>>
    get_population_and_fitness() const override;

    virtual std::unique_ptr<OptimizerBase>
    clone() override;

    int
    get_optimizer_id() const override {
        return WOA;
    }

    void
    set_population_with_fitness(const std::vector<std::vector<double>> &population,
                                const std::vector<double> &fitness) override;

    void
    run(bool initialize_flag = true) override;

  private:
    double lower_bound_;
    double upper_bound_;
    std::vector<double> lower_bound_vector_;
    std::vector<double> upper_bound_vector_;
    uint32_t n_dimensions_;
    std::function<double(const std::vector<double> &)> fitness_function_;
    std::vector<double> fitness_values_;
    std::vector<double> convergence_curve_;
    std::vector<double> leader_pos_;
    std::vector<std::vector<double>> positions_;
    double leader_score_;
    random_gen::Rng rng_;

    void
    configure();
    void
    initialize();
    void
    initialize(const std::vector<std::vector<double>> &migrated_solutions);
    void
    initialize_population();
    void
    calculate_fitness();
    void
    update_leader();
};

#endif // WOA_HPP