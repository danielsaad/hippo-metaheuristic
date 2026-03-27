#include "ho/hippo_optimizer.hpp"
#include <algorithm>
#include <cstdint>
#include <iostream>
#include <random>

HippoOptimizer::HippoOptimizer(uint32_t n_hippo, uint32_t max_iterations,
                               std::unique_ptr<ProblemBase> objective_function)
    : OptimizerBase(n_hippo, max_iterations, std::move(objective_function)), n_hippo(n_hippo) {
    lowerbound_ = objective_function_->lowerbound()[0]; // Assuming all dimensions have the same bounds
    upperbound_ = objective_function_->upperbound()[0];
    std::cout << "Initialized HippoOptimizer with " << n_hippo << " hippos, max iterations: " << max_iterations_
              << ", lower bound: " << lowerbound_ << ", upper bound: " << upperbound_ << "\n";
    n_hippo = n_agents_;
    n_dimensions_ = objective_function_->n_dimensions();
    fitness_function = [this](const vector<double> &x) { return objective_function_->evaluate(x); };
}

void HippoOptimizer::run() {
    initialize();
    std::cout << "Running HippoOptimizer...\n" << max_iterations_ << " iterations, " << n_hippo << " hippos, " << n_dimensions_ << " dimensions.\n";
    vector<double> best_global; // best hippo globally
    double fbest_global;        // best fitness globally
    uint32_t best_idx_global;   // best idx globally
    // main loop
    for (uint32_t t = 0; t < max_iterations_; t++) {
        std::cout << "Iteration " << t + 1 << "/" << max_iterations_ << "\n";
        vector<double> best;
        double fbest;
        uint32_t best_idx;
        // get best solution
        auto it = std::min_element(fitness_vector.begin(), fitness_vector.end());
        fbest = *it;
        best_idx = std::distance(fitness_vector.begin(), it);
        if (t == 0 or fbest < fbest_global) {
            fbest_global = fbest;
            best_idx_global = best_idx;
            best_global = population[best_idx_global];
        }
        explore(best_idx, t);
        defend();
        escape(t);
        best_fitness_ = fbest_global;
        best_solution_ = best_global;
        std::cout << "Best so far " << fbest_global << " (";
        for (const auto &hippo : best_global) {
            std::cout << hippo << " ";
        }
        std::cout << ") at iteration " << t + 1 << "\n";
    }
}

/**
 * @brief  Phase 1 of the optimization. Update hippos positions in the river or pond.
 * @param  best_idx index of the best hippo
 * @param iteration currenct iteration
 **/
void HippoOptimizer::initialize() {
    lowerbound_vector.resize(n_dimensions_, lowerbound_);
    upperbound_vector.resize(n_dimensions_, upperbound_);
    population = vector<vector<double>>(n_hippo, vector<double>(n_dimensions_));
    auto uniform_gen = UniformDist<double>(0, 1);
    for (uint32_t j = 0; j < n_dimensions_; j++) {
        auto rand_column = uniform_gen.generate_uniform_dist_matrix(n_hippo, 1);
        for (uint32_t i = 0; i < n_hippo; i++) {
            population[i][j] =
                lowerbound_vector[j] + rand_column[i][0] * (upperbound_vector[j] - lowerbound_vector[j]);
        }
    }
    fitness_vector.resize(n_hippo);
    for (size_t i = 0; i < n_hippo; i++) {
        fitness_vector[i] = fitness_function(population[i]);
    }
}

void HippoOptimizer::explore(uint32_t best_idx, uint32_t iteration) {
    // Phase 1: exploration. Update hippos positions in the river or pond
    auto dominant_hippo = population[best_idx];
    vector<vector<double>> population_p1(n_hippo, vector<double>(n_dimensions_));
    vector<vector<double>> population_p2(n_hippo, vector<double>(n_dimensions_));

    for (uint32_t i = 0; i < n_hippo / 2; i++) {
        auto r1 = UniformDist<int>(1, 2).generate();
        auto r2 = UniformDist<int>(1, 2).generate();
        auto ip1 = UniformDist<int>(0, 1).generate_uniform_dist_vector(2);
        auto rand_group_n = UniformDist<int>(1, n_hippo).generate();
        auto rand_group = RandomPermutation(n_hippo).generate(rand_group_n);

        // Mean of random group
        vector<double> mean(n_dimensions_, 0.0);
        if (rand_group_n > 1) {
            for (uint32_t k = 0; k < n_dimensions_; k++) {
                for (uint32_t j = 0; j < rand_group_n; j++) {
                    mean[k] += population[rand_group[j]][k];
                }
                mean[k] /= rand_group_n;
            }
        } else {
            mean = population[rand_group[0]];
        }
        vector<vector<double>> alfa_matrix(5);
        // Alfa 1
        alfa_matrix[0] = UniformDist<double>(0, 1).generate_uniform_dist_vector(n_dimensions_);
        std::transform(alfa_matrix[0].begin(), alfa_matrix[0].end(), alfa_matrix[0].begin(),
                       [r2, ip1](double x) { return r2 * x + (1 - ip1[0]); });

        // Alfa 2
        alfa_matrix[1] = UniformDist<double>(0, 1).generate_uniform_dist_vector(n_dimensions_);
        std::transform(alfa_matrix[1].begin(), alfa_matrix[1].end(), alfa_matrix[1].begin(),
                       [](double x) { return x * 2 - 1; });

        // Alfa 3
        alfa_matrix[2] = UniformDist<double>(0, 1).generate_uniform_dist_vector(n_dimensions_);

        // Alfa 4
        alfa_matrix[3] = UniformDist<double>(0, 1).generate_uniform_dist_vector(n_dimensions_);
        std::transform(alfa_matrix[3].begin(), alfa_matrix[3].end(), alfa_matrix[3].begin(),
                       [r1, ip1](double x) { return r1 * x + (1 - ip1[1]); });

        // Alfa 5
        alfa_matrix[4] = vector<double>(n_dimensions_, UniformDist<double>(0, 1).generate());

        auto &alfa_a = alfa_matrix[UniformDist<int>(0, 4).generate()];
        auto &alfa_b = alfa_matrix[UniformDist<int>(0, 4).generate()];

        double r = UniformDist<double>(0, 1).generate();
        for (size_t j = 0; j < population_p1[i].size(); j++) {
            population_p1[i][j] = population[i][j] + r * (dominant_hippo[j] - r1 * population[i][j]);
        }

        double t = std::exp((double)-iteration / (max_iterations_ - 1)); // 0-based indexing

        if (t > 0.6) {
            for (size_t j = 0; j < population_p2[i].size(); j++) {
                population_p2[i][j] = population[i][j] + alfa_a[j] * (dominant_hippo[j] - r2 * mean[j]);
            }
        } else if (UniformDist<double>(0, 1).generate() < 0.5) {
            for (size_t j = 0; j < population_p2[i].size(); j++) {
                population_p2[i][j] = population[i][j] + alfa_b[j] * (mean[j] - dominant_hippo[j]);
            }
        } else {
            double res = (upperbound_ - lowerbound_) * UniformDist<double>(0, 1).generate() + lowerbound_;
            for (size_t j = 0; j < population_p2[i].size(); j++) {
                population_p2[i][j] = res;
            }
        }

        for (size_t j = 0; j < population_p1[i].size(); j++) {
            population_p1[i][j] = std::min(std::max(population_p1[i][j], lowerbound_), upperbound_);
        }
        for (size_t j = 0; j < population_p2[i].size(); j++) {
            population_p2[i][j] = std::min(std::max(population_p2[i][j], lowerbound_), upperbound_);
        }
        auto fitness_p1 = fitness_function(population_p1[i]);
        if (fitness_p1 < fitness_vector[i]) {
            population[i] = population_p1[i];
            fitness_vector[i] = fitness_p1;
        }
        auto fitness_p2 = fitness_function(population_p2[i]);
        if (fitness_p2 < fitness_vector[i]) {
            population[i] = population_p2[i];
            fitness_vector[i] = fitness_p2;
        }
    }
}

/**
 * @brief  Phase 2 of the optimization. Defend against predators.
 *
 */
void HippoOptimizer::defend() {
    for (size_t i = n_hippo / 2; i < n_hippo; i++) {
        vector<double> predator(n_dimensions_);
        double r = UniformDist<double>(0, 1).generate();
        for (auto &p : predator) {
            p = lowerbound_ + r * (upperbound_ - lowerbound_);
        }
        auto fitness_hl = fitness_function(predator);
        vector<double> distance_to_leader(n_dimensions_);
        for (size_t j = 0; j < distance_to_leader.size(); j++) {
            distance_to_leader[j] = std::abs(predator[j] - population[i][j]);
        }
        auto b = UniformDist<double>(2, std::nextafter(4, std::numeric_limits<double>::max())).generate();
        auto c = UniformDist<double>(1, std::nextafter(1.5, std::numeric_limits<double>::max())).generate();
        auto d = UniformDist<double>(2, std::nextafter(3, std::numeric_limits<double>::max())).generate();
        auto l = UniformDist<double>(-2 * std::numbers::pi,
                                     std::nextafter(2 * std::numbers::pi, std::numeric_limits<double>::max()))
                     .generate();
        auto rl = levy(n_hippo, n_dimensions_, 1.5);
        std::for_each(rl.begin(), rl.end(), [](std::vector<double> &v) {
            std::for_each(v.begin(), v.end(), [](double &x) { x *= 0.05; });
        });
        vector<vector<double>> population_p3(n_hippo, vector<double>(n_dimensions_));
        if (fitness_vector[i] > fitness_hl) {
            for (size_t j = 0; j < population_p3[i].size(); j++) {
                population_p3[i][j] =
                    rl[i][j] * predator[j] + (b / (c - d * std::cos(l))) * (1 / distance_to_leader[j]);
            }
        } else {
            auto r = UniformDist<double>(0, 1).generate_uniform_dist_vector(n_dimensions_);
            for (size_t j = 0; j < population_p3[i].size(); j++) {
                population_p3[i][j] = rl[i][j] * predator[j] +
                                      (b / (c - d * std::cos(l))) * (1 / (2 * distance_to_leader[j] + r[j]));
            }
        }
        for (size_t j = 0; j < population_p3[i].size(); j++) {
            population_p3[i][j] = std::min(std::max(population_p3[i][j], lowerbound_), upperbound_);
        }
        double fitness_p3 = fitness_function(population_p3[i]);
        if (fitness_p3 < fitness_vector[i]) {
            population[i] = population_p3[i];
            fitness_vector[i] = fitness_p3;
        }
    }
}

void HippoOptimizer::escape(uint32_t iteration) {
    for (size_t i = 0; i < n_hippo; i++) {
        vector<double> lo_local(n_dimensions_, lowerbound_ / iteration);
        vector<double> hi_local(n_dimensions_, upperbound_ / iteration);
        vector<vector<double>> alfa_matrix(3, vector<double>(n_dimensions_));
        alfa_matrix[0] = UniformDist<double>(0, 1).generate_uniform_dist_vector(n_dimensions_);
        std::transform(alfa_matrix[0].begin(), alfa_matrix[0].end(), alfa_matrix[0].begin(),
                       [](double x) { return 2 * x - 1; });
        double r = UniformDist<double>(0, 1).generate();
        alfa_matrix[2] = vector<double>(n_dimensions_, r);
        r = NormalDist(0, 1).generate();
        alfa_matrix[1] = vector<double>(n_dimensions_, r);
        uint32_t idx = UniformDist<int>(0, 2).generate();
        auto &d = alfa_matrix[idx];
        vector<double> population_p4(n_dimensions_);
        for (size_t j = 0; j < population_p4.size(); j++) {
            double r = UniformDist<double>(0, 1).generate();
            population_p4[j] = population[i][j] + r * (lo_local[j] + d[j] * (hi_local[j] - lo_local[j]));
            population_p4[j] = std::min(std::max(population_p4[j], lowerbound_), upperbound_);
        }
        auto fitness_p4 = fitness_function(population_p4);
        if (fitness_p4 < fitness_vector[i]) {
            population[i] = population_p4;
            fitness_vector[i] = fitness_p4;
        }
    }
}
