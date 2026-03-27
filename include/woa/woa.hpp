#ifndef WOA_HPP
#define WOA_HPP

#include "core/optimizer.hpp"
#include "core/problem.hpp"
#include "random/random_gen.hpp"
#include <random>
#include <vector>
class Woa : public OptimizerBase {
  public:
    Woa(uint32_t n_agents, uint32_t max_it, std::unique_ptr<ProblemBase> objective_function)
        : OptimizerBase(n_agents, max_it, std::move(objective_function)) {}

    virtual void run() override {
        initialize();
        for (uint32_t it = 0; it < max_iterations_; it++) {
            for (auto &agent : positions_) {
                for (auto &pos : agent) {
                    pos = std::clamp(pos, lower_bound_, upper_bound_);
                }
            }
            update_leader();
            double a = 2.0 - it * (2.0 / max_iterations_);
            double a2 = -1.0 + it * (-1.0 / max_iterations_);
            auto dist_real_uniform = std::uniform_real_distribution<double>(0.0, 1.0);
            for (size_t i = 0; i < n_agents_; i++) {
                auto r1 = rng_.rnd(dist_real_uniform);
                auto r2 = rng_.rnd(dist_real_uniform);
                double a_coef = 2 * a * r1 - a;
                double c_coef = 2 * r2;
                double b = 1;
                double l = (a2 - 1) * rng_.rnd(dist_real_uniform) + 1;
                double p = rng_.rnd(dist_real_uniform);
                for (size_t j = 0; j < n_dimensions_; j++) {
                    if (p < 0.5) {
                        if (std::abs(a_coef) >= 1) {
                            uint32_t rnd_leader_idx = n_agents_ * rng_.rnd(dist_real_uniform);
                            const auto &x_rand = positions_[rnd_leader_idx];
                            double d_x_rand = abs(c_coef * x_rand[j] - positions_[i][j]);
                            positions_[i][j] = x_rand[j] - a_coef * d_x_rand;

                        } else {
                            double d_leader = std::abs(c_coef * leader_pos_[j] - positions_[i][j]);
                            positions_[i][j] = leader_pos_[j] - a_coef * d_leader;
                        }
                    } else {
                        double distance_to_leader = std::abs(leader_pos_[j] - positions_[i][j]);
                        positions_[i][j] =
                            distance_to_leader * exp(b * l) * cos(l * 2 * std::numbers::pi) + leader_pos_[j];
                    }
                }
            }
            convergence_curve_[it] = leader_score_;
        }
    }

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

    void initialize() {
        n_dimensions_ = objective_function_->n_dimensions();
        lower_bound_vector_ = objective_function_->lowerbound();
        upper_bound_vector_ = objective_function_->upperbound();
        lower_bound_ = lower_bound_vector_[0];
        upper_bound_ = upper_bound_vector_[0];
        leader_pos_ = std::vector<double>(n_dimensions_, 0.0);
        leader_score_ = std::numeric_limits<double>::infinity();
        convergence_curve_ = std::vector<double>(max_iterations_, 0.0);
        lower_bound_vector_ = std::vector<double>(n_dimensions_, lower_bound_);
        upper_bound_vector_ = std::vector<double>(n_dimensions_, upper_bound_);
        initialize_population();
    }

    void initialize_population() {
        auto n_boundary = n_dimensions_ / 2;
        auto dist = std::uniform_real_distribution<double>(lower_bound_, upper_bound_);
        positions_ = rng_.matrix<double>(n_agents_, n_dimensions_, dist);
        fitness_values_ = std::vector<double>(n_agents_);
    }
    void calculate_fitness() {
        for (size_t i = 0; i < positions_.size(); i++) {
            fitness_values_[i] = objective_function_->evaluate(positions_[i]);
        }
    }

    void update_leader() {
        calculate_fitness();
        uint32_t leader_idx = 0;
        for (size_t i = 0; i < n_agents_; i++) {
            if (fitness_values_[i] < leader_score_) {
                leader_idx = i;
                leader_score_ = fitness_values_[i];
            }
        }
        leader_pos_ = positions_[leader_idx];
        best_solution_ = leader_pos_;
        best_fitness_ = leader_score_;
    }
};

#endif // WOA_HPP