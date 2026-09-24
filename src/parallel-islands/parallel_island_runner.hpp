#ifndef PARALLEL_ISLAND_RUNNER_HPP
#define PARALLEL_ISLAND_RUNNER_HPP

#include "parallel-islands/homogeneous_island.hpp"
#include "parallel-islands/parallel_island_manager.hpp"
#include "parallel_island_manager.hpp"
#include <algorithm>
#include <vector>

class ParallelIslandRunner {
  public:
    ParallelIslandRunner(size_t n_threads, std::vector<HomogeneousIsland> islands, size_t n_generations,
                         size_t migration_rate)
        : n_threads_(n_threads), n_generations_(n_generations), migration_rate_(migration_rate),
          islands_(std::move(islands)) {};

    void run();
    void set_policy(ParallelIslandManager &&manager) { manager_ = std::move(manager); }

  private:
    tuple<vector<vector<double>>, vector<double>> select_individuals(HomogeneousIsland &island) {
        auto [p, f] = island.optimizer_->get_population_and_fitness();
        auto [migrants, fitness] = manager_.select_individuals(p, f);
        return std::make_tuple(migrants, fitness);
    }

  private:
    size_t n_threads_;
    size_t n_generations_;
    size_t migration_rate_;
    std::vector<HomogeneousIsland> islands_;
    ParallelIslandManager manager_;
};

#endif // PARALLEL_ISLAND_RUNNER_HPP