#ifndef GWO_HPP
#define GWO_HPP
#include "core/optimizer.hpp"
#include "core/optimizer_factory.hpp"
#include "random/random_gen.hpp"
#include <algorithm>
#include <limits>
#include <numeric>
#include <stdexcept>

class Gwo : public OptimizerBase {
  private:
    std::vector<std::vector<double>> population_;
    std::vector<double> alpha_pos_, beta_pos_, delta_pos_;
    double alpha_score_ = std::numeric_limits<double>::max();
    double beta_score_ = std::numeric_limits<double>::max();
    double delta_score_ = std::numeric_limits<double>::max();
    uint32_t n_dimension;
    double lowerbound_, upperbound_;
    std::vector<double> lowerbound_vector, upperbound_vector;
    std::vector<double> fitness_vector_;
    random_gen::Rng rng_;

  public:
    Gwo(uint32_t n_agents, uint32_t max_iterations, std::unique_ptr<ProblemBase> objective_function)
        : OptimizerBase(n_agents, max_iterations, std::move(objective_function)) {
        n_dimension = objective_function_->n_dimensions();
        lowerbound_ = objective_function_->lowerbound()[0];
        upperbound_ = objective_function_->upperbound()[0];
        lowerbound_vector = objective_function_->lowerbound();
        upperbound_vector = objective_function_->upperbound();
    }

    ~Gwo() = default;

    virtual int
    get_optimizer_id() const override {
        return GWO;
    }

    virtual void
    set_population_with_fitness(const std::vector<std::vector<double>> &population,
                                const std::vector<double> &fitness) override {
        if (population.size() != fitness.size()) {
            throw std::invalid_argument("GWO population and fitness sizes must match");
        }
        for (const auto &agent : population) {
            if (agent.size() != n_dimension) {
                throw std::invalid_argument("GWO population agents must match the problem dimension");
            }
        }
        n_agents_ = static_cast<uint32_t>(population.size());
        population_ = population;
        fitness_vector_ = fitness;
        std::vector<size_t> order(population.size());
        std::iota(order.begin(), order.end(), 0);
        std::ranges::sort(order, {}, [&](size_t i) { return fitness[i]; });
        alpha_score_ = beta_score_ = delta_score_ = std::numeric_limits<double>::max();
        alpha_pos_ = beta_pos_ = delta_pos_ = vector<double>(n_dimension, 0.0);
        if (!order.empty()) {
            alpha_score_ = fitness[order[0]];
            alpha_pos_ = population[order[0]];
            update_best_solution(alpha_pos_, alpha_score_);
        }
        if (order.size() > 1) {
            beta_score_ = fitness[order[1]];
            beta_pos_ = population[order[1]];
        }
        if (order.size() > 2) {
            delta_score_ = fitness[order[2]];
            delta_pos_ = population[order[2]];
        } else {
            delta_score_ = beta_score_;
            delta_pos_ = beta_pos_;
        }
    }

    virtual std::tuple<std::vector<std::vector<double>>, std::vector<double>>
    get_population_and_fitness() const override {
        return std::make_tuple(population_, fitness_vector_);
    }

    virtual std::unique_ptr<OptimizerBase>
    clone() override {
        return std::make_unique<Gwo>(n_agents_, max_iterations_, objective_function_->clone());
    }

    virtual void
    run(bool initialize_flag = true) override {
        auto random_dist = std::uniform_real_distribution<double>(0.0, 1.0);
        if (initialize_flag) {
            initialize_population();
        } else if (population_.size() != n_agents_ or fitness_vector_.size() != n_agents_) {
            throw std::logic_error("GWO must receive a complete population before run(false)");
        }
        // Put wolves back in the search space if they go out of bounds
        for (uint32_t it = 0; it < max_iterations_; it++) {
            for (auto &agent : population_) {
                for (size_t j = 0; j < n_dimension; j++) {
                    agent[j] = std::clamp(agent[j], lowerbound_vector[j], upperbound_vector[j]);
                }
            }
            // Compute fitness for each agent and update alpha, beta, and delta positions and scores
            for (uint32_t i = 0; i < n_agents_; i++) {
                fitness_vector_[i] = objective_function_->evaluate(population_[i]);
                if (fitness_vector_[i] < alpha_score_) {
                    alpha_score_ = fitness_vector_[i];
                    alpha_pos_ = population_[i];
                } else if (fitness_vector_[i] < beta_score_) {
                    beta_score_ = fitness_vector_[i];
                    beta_pos_ = population_[i];
                } else if (fitness_vector_[i] < delta_score_) {
                    delta_score_ = fitness_vector_[i];
                    delta_pos_ = population_[i];
                }
            }
            // a decreases linearly from 2 to 0
            double a = 2.0 - it * (2.0 / max_iterations_);
            for (uint32_t i = 0; i < n_agents_; i++) {
                for (size_t j = 0; j < n_dimension; j++) {
                    double r1 = rng_.rnd(random_dist);
                    double r2 = rng_.rnd(random_dist);
                    double A1 = 2 * a * r1 - a;
                    double C1 = 2 * r2;
                    double D_alpha = std::abs(C1 * alpha_pos_[j] - population_[i][j]);
                    double X1 = alpha_pos_[j] - A1 * D_alpha;

                    r1 = rng_.rnd(random_dist);
                    r2 = rng_.rnd(random_dist);
                    double A2 = 2 * a * r1 - a;
                    double C2 = 2 * r2;
                    double D_beta = std::abs(C2 * beta_pos_[j] - population_[i][j]);
                    double X2 = beta_pos_[j] - A2 * D_beta;

                    r1 = rng_.rnd(random_dist);
                    r2 = rng_.rnd(random_dist);
                    double A3 = 2 * a * r1 - a;
                    double C3 = 2 * r2;
                    double D_delta = std::abs(C3 * delta_pos_[j] - population_[i][j]);
                    double X3 = delta_pos_[j] - A3 * D_delta;

                    population_[i][j] = (X1 + X2 + X3) / 3.0;
                }
            }
        }
        update_best_solution(alpha_pos_, alpha_score_);
        convergence_curve_.push_back(alpha_score_);
    }

  private:
    void
    initialize_population() {
        auto random_dist = std::uniform_real_distribution<double>(0.0, 1.0);
        fitness_vector_.assign(n_agents_, std::numeric_limits<double>::max());
        alpha_score_ = beta_score_ = delta_score_ = std::numeric_limits<double>::max();
        alpha_pos_ = beta_pos_ = delta_pos_ = vector<double>(n_dimension, 0.0);
        population_.assign(n_agents_, vector<double>(n_dimension, 0.0));
        for (uint32_t i = 0; i < n_agents_; i++) {
            for (uint32_t j = 0; j < n_dimension; j++) {
                population_[i][j] = lowerbound_vector[j] + rng_.rnd(random_dist) *
                                                               (upperbound_vector[j] - lowerbound_vector[j]);
            }
        }
    }
};

#endif
