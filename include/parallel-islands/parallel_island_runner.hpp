#ifndef PARALLEL_ISLAND_RUNNER_HPP
#define PARALLEL_ISLAND_RUNNER_HPP

#include "parallel-islands/homogeneous_island.hpp"
#include <algorithm>
#include <vector>

class ParallelIslandRunner {
  public:
    ParallelIslandRunner(size_t n_threads, std::vector<HomogeneousIsland> islands, size_t n_migrations)
        : n_threads_(n_threads), n_migrations_(n_migrations), islands_(std::move(islands)) {};

    void run();

  private:
    ParallelIslandManager manager_;
    std::vector<std::vector<double>>
    extract_individuals(std::vector<std::tuple<std::vector<double>, double>> population_with_fitness) {
        std::vector<std::vector<double>> individuals;
        std::sort(population_with_fitness.begin(), population_with_fitness.end(),
                  [](const auto &a, const auto &b) { return std::get<1>(a) < std::get<1>(b); });
        // get best solution from each island
        individuals.push_back(std::get<0>(population_with_fitness.front()));
        // get worst solution from each island
        individuals.push_back(std::get<0>(population_with_fitness.back()));
        // get medium solution from each island
        int half_n = population_with_fitness.size() / 2;
        individuals.push_back(std::get<0>(population_with_fitness[half_n]));
        return individuals;
    }

  private:
    size_t n_threads_;
    size_t n_migrations_;
    std::vector<HomogeneousIsland> islands_;
};

#endif // PARALLEL_ISLAND_RUNNER_HPP