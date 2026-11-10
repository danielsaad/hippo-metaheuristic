#include "woa.hpp"
#include <algorithm>
#include <stdexcept>

void
Woa::initialize_population() {
    auto n_boundary = n_dimensions_ / 2;
    auto dist = std::uniform_real_distribution<double>(lower_bound_, upper_bound_);
    positions_ = rng_.matrix<double>(n_agents_, n_dimensions_, dist);
    fitness_values_ = std::vector<double>(n_agents_);
}

void
Woa::calculate_fitness() {
    for (size_t i = 0; i < positions_.size(); i++) {
        fitness_values_[i] = objective_function_->evaluate(positions_[i]);
    }
}

void
Woa::update_leader() {
    calculate_fitness();
    for (size_t i = 0; i < n_agents_; i++) {
        if (fitness_values_[i] < leader_score_) {
            leader_score_ = fitness_values_[i];
            leader_pos_ = positions_[i];
        }
    }
    update_best_solution(leader_pos_, leader_score_);
}

std::tuple<std::vector<std::vector<double>>, std::vector<double>>
Woa::get_population_and_fitness() const {
    return std::make_tuple(positions_, fitness_values_);
}

std::unique_ptr<OptimizerBase>
Woa::clone() {
    return std::make_unique<Woa>(n_agents_, max_iterations_, objective_function_->clone());
}

void
Woa::set_population_with_fitness(const std::vector<std::vector<double>> &population,
                                 const std::vector<double> &fitness) {
    if (population.size() != fitness.size() || population.size() != n_agents_) {
        throw std::invalid_argument("WOA population and fitness sizes must match the configured population");
    }
    for (const auto &agent : population) {
        if (agent.size() != n_dimensions_) {
            throw std::invalid_argument("WOA population agents must match the problem dimension");
        }
    }
    positions_ = population;
    fitness_values_ = fitness;
    auto best = std::min_element(fitness.begin(), fitness.end());
    if (best != fitness.end() && *best < leader_score_) {
        auto index = std::distance(fitness.begin(), best);
        leader_score_ = *best;
        leader_pos_ = population[index];
    }
    update_best_solution(leader_pos_, leader_score_);
}

void
Woa::run(bool initialize_flag) {
    std::print("Running WOA with {} agents, max iterations: {}\n", n_agents_, max_iterations_);
    if (initialize_flag) {
        initialize_population();
    }
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
                        double d_x_rand = std::abs(c_coef * x_rand[j] - positions_[i][j]);
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
    // Keep population and fitness consistent after the last position update.
    for (auto &agent : positions_) {
        for (auto &pos : agent) {
            pos = std::clamp(pos, lower_bound_, upper_bound_);
        }
    }
    update_leader();
}

void
Woa::configure() {
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
}

void
Woa::initialize() {
    initialize_population();
}

void
Woa::initialize(const std::vector<std::vector<double>> &migrated_solutions) {
    for (size_t i = 0; i < std::min(migrated_solutions.size(), positions_.size()); ++i) {
        auto solution = migrated_solutions[i];
        for (size_t j = 0; j < solution.size(); ++j) {
            solution[j] = std::clamp(solution[j], lower_bound_, upper_bound_);
        }
        positions_[i] = solution;
        fitness_values_[i] = objective_function_->evaluate(solution);
    }
}
