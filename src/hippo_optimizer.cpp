#include "hippo_optimizer.h"
#include <algorithm>
#include <cstdint>
#include <iostream>
#include <random>

hippo_optimizer::hippo_optimizer(uint32_t n_hippo, uint32_t max_iterations, double lowerbound,
                                 double upperbound, uint32_t n_dimensions, const fun &fitness)
    : n_hippo(n_hippo), max_iterations(max_iterations), lowerbound(lowerbound), upperbound(upperbound),
      n_dimensions(n_dimensions), fitness(fitness) {}

void hippo_optimizer::run() {
    initialize();
    vector<double> best_global; // best hippo globally
    double fbest_global;        // best fitness globally
    uint32_t best_idx_global;   // best idx globally
    // main loop
    for (uint32_t t = 0; t < max_iterations; t++) {
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
        best_fitness = fbest_global;
        best_solution = best_global;
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
void hippo_optimizer::initialize() {
    lowerbound_vector.resize(n_dimensions, lowerbound);
    upperbound_vector.resize(n_dimensions, upperbound);
    population = vector<vector<double>>(n_hippo, vector<double>(n_dimensions));
    auto uniform_gen = uniform_dist<double>(0, 1);
    for (uint32_t j = 0; j < n_dimensions; j++) {
        auto rand_column = uniform_gen.generate_uniform_dist_matrix(n_hippo, 1);
        for (uint32_t i = 0; i < n_hippo; i++) {
            population[i][j] =
                lowerbound_vector[j] + rand_column[i][0] * (upperbound_vector[j] - lowerbound_vector[j]);
        }
    }
    fitness_vector.resize(n_hippo);
    for (size_t i = 0; i < n_hippo; i++) {
        fitness_vector[i] = fitness(population[i]);
    }
}

void hippo_optimizer::explore(uint32_t best_idx, uint32_t iteration) {
    // Phase 1: exploration. Update hippos positions in the river or pond
    auto dominant_hippo = population[best_idx];
    vector<vector<double>> population_p1(n_hippo, vector<double>(n_dimensions));
    vector<vector<double>> population_p2(n_hippo, vector<double>(n_dimensions));

    for (uint32_t i = 0; i < n_hippo / 2; i++) {
        auto r1 = uniform_dist<int>(1, 2).generate();
        auto r2 = uniform_dist<int>(1, 2).generate();
        auto ip1 = uniform_dist<int>(0, 1).generate_uniform_dist_vector(2);
        auto rand_group_n = uniform_dist<int>(1, n_hippo).generate();
        auto rand_group = random_permutation(n_hippo).generate(rand_group_n);

        // Mean of random group
        vector<double> mean(n_dimensions, 0.0);
        if (rand_group_n > 1) {
            for (uint32_t k = 0; k < n_dimensions; k++) {
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
        alfa_matrix[0] = uniform_dist<double>(0, 1).generate_uniform_dist_vector(n_dimensions);
        std::transform(alfa_matrix[0].begin(), alfa_matrix[0].end(), alfa_matrix[0].begin(),
                       [r2, ip1](double x) { return r2 * x + (1 - ip1[0]); });

        // Alfa 2
        alfa_matrix[1] = uniform_dist<double>(0, 1).generate_uniform_dist_vector(n_dimensions);
        std::transform(alfa_matrix[1].begin(), alfa_matrix[1].end(), alfa_matrix[1].begin(),
                       [](double x) { return x * 2 - 1; });

        // Alfa 3
        alfa_matrix[2] = uniform_dist<double>(0, 1).generate_uniform_dist_vector(n_dimensions);

        // Alfa 4
        alfa_matrix[3] = uniform_dist<double>(0, 1).generate_uniform_dist_vector(n_dimensions);
        std::transform(alfa_matrix[3].begin(), alfa_matrix[3].end(), alfa_matrix[3].begin(),
                       [r1, ip1](double x) { return r1 * x + (1 - ip1[1]); });

        // Alfa 5
        alfa_matrix[4] = vector<double>(n_dimensions, uniform_dist<double>(0, 1).generate());

        auto &alfa_a = alfa_matrix[uniform_dist<int>(0, 4).generate()];
        auto &alfa_b = alfa_matrix[uniform_dist<int>(0, 4).generate()];

        double r = uniform_dist<double>(0, 1).generate();
        for (size_t j = 0; j < population_p1[i].size(); j++) {
            population_p1[i][j] = population[i][j] + r * (dominant_hippo[j] - r1 * population[i][j]);
        }

        double t = std::exp((double)-iteration / (max_iterations - 1)); // 0-based indexing

        if (t > 0.6) {
            for (size_t j = 0; j < population_p2[i].size(); j++) {
                population_p2[i][j] = population[i][j] + alfa_a[j] * (dominant_hippo[j] - r2 * mean[j]);
            }
        } else if (uniform_dist<double>(0, 1).generate() < 0.5) {
            for (size_t j = 0; j < population_p2[i].size(); j++) {
                population_p2[i][j] = population[i][j] + alfa_b[j] * (mean[j] - dominant_hippo[j]);
            }
        } else {
            double res = (upperbound - lowerbound) * uniform_dist<double>(0, 1).generate() + lowerbound;
            for (size_t j = 0; j < population_p2[i].size(); j++) {
                population_p2[i][j] = res;
            }
        }

        for (size_t j = 0; j < population_p2[i].size(); j++) {
            population_p2[i][j] = std::min(std::max(population_p2[i][j], lowerbound), upperbound);
        }
        auto fitness_p1 = fitness(population_p1[i]);
        if (fitness_p1 < fitness_vector[i]) {
            population[i] = population_p1[i];
            fitness_vector[i] = fitness_p1;
        }
        auto fitness_p2 = fitness(population_p2[i]);
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
void hippo_optimizer::defend() {
    for (size_t i = n_hippo / 2; i < n_hippo; i++) {
        vector<double> predator(n_dimensions);
        double r = uniform_dist<double>(0, 1).generate();
        for (auto &p : predator) {
            p = lowerbound + r * (upperbound - lowerbound);
        }
        auto fitness_hl = fitness(predator);
        vector<double> distance_to_leader(n_dimensions);
        for (size_t j = 0; j < distance_to_leader.size(); j++) {
            distance_to_leader[j] = std::abs(predator[j] - population[i][j]);
        }
        auto b = uniform_dist<double>(2, std::nextafter(4, std::numeric_limits<double>::max())).generate();
        auto c = uniform_dist<double>(1, std::nextafter(1.5, std::numeric_limits<double>::max())).generate();
        auto d = uniform_dist<double>(2, std::nextafter(3, std::numeric_limits<double>::max())).generate();
        auto l =
            uniform_dist<double>(-2 * std::numbers::pi,
                                 std::nextafter(2 * std::numbers::pi, std::numeric_limits<double>::max()))
                .generate();
        auto rl = levy(n_hippo, n_dimensions, 1.5);
        std::for_each(rl.begin(), rl.end(), [](std::vector<double> &v) {
            std::for_each(v.begin(), v.end(), [](double &x) { x *= 0.05; });
        });
        vector<vector<double>> population_p3(n_hippo, vector<double>(n_dimensions));
        if (fitness_vector[i] > fitness_hl) {
            for (size_t j = 0; j < population_p3[i].size(); j++) {
                population_p3[i][j] =
                    rl[i][j] * predator[j] + (b / (c - d * std::cos(l))) * (1 / distance_to_leader[j]);
            }
        } else {
            auto r = uniform_dist<double>(0, 1).generate_uniform_dist_vector(n_dimensions);
            for (size_t j = 0; j < population_p3[i].size(); j++) {
                population_p3[i][j] = rl[i][j] * predator[j] +
                                      (b / (c - d * std::cos(l))) * (1 / (2 * distance_to_leader[j] + r[j]));
            }
        }
        for (size_t j = 0; j < population_p3[i].size(); j++) {
            population_p3[i][j] = std::min(std::max(population_p3[i][j], lowerbound), upperbound);
        }
        double fitness_p3 = fitness(population_p3[i]);
        if (fitness_p3 < fitness_vector[i]) {
            population[i] = population_p3[i];
            fitness_vector[i] = fitness_p3;
        }
    }
}

void hippo_optimizer::escape(uint32_t iteration) {
    for (size_t i = 0; i < n_hippo; i++) {
        vector<double> lo_local(n_dimensions, lowerbound / iteration);
        vector<double> hi_local(n_dimensions, upperbound / iteration);
        vector<vector<double>> alfa_matrix(3, vector<double>(n_dimensions));
        alfa_matrix[0] = uniform_dist<double>(0, 1).generate_uniform_dist_vector(n_dimensions);
        std::transform(alfa_matrix[0].begin(), alfa_matrix[0].end(), alfa_matrix[0].begin(),
                       [](double x) { return 2 * x - 1; });
        double r = uniform_dist<double>(0, 1).generate();
        alfa_matrix[2] = vector<double>(n_dimensions, r);
        r = normal_dist(0, 1).generate();
        alfa_matrix[1] = vector<double>(n_dimensions, r);
        uint32_t idx = uniform_dist<int>(0, 2).generate();
        auto &d = alfa_matrix[idx];
        vector<double> population_p4(n_dimensions);
        for (size_t j = 0; j < population_p4.size(); j++) {
            double r = uniform_dist<double>(0, 1).generate();
            population_p4[j] = population[i][j] + r * (lo_local[j] + d[j] * (hi_local[j] - lo_local[j]));
            population_p4[j] = std::min(std::max(population_p4[j], lowerbound), upperbound);
        }
        auto fitness_p4 = fitness(population_p4);
        if (fitness_p4 < fitness_vector[i]) {
            population[i] = population_p4;
            fitness_vector[i] = fitness_p4;
        }
    }
}

std::tuple<vector<double>, double> hippo_optimizer::get_best_solution() const {
    return {best_solution, best_fitness};
}