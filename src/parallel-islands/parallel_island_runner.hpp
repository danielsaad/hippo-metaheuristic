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
                         size_t migration_rate, size_t reconfiguration_rate);

    void
    run();

    void
    set_manager(ParallelIslandManager &&manager);

  private:
    tuple<vector<vector<double>>, vector<double>>
    select_individuals(HomogeneousIsland &island);

  private:
    size_t n_threads_;
    size_t n_generations_;
    size_t migration_rate_;
    size_t reconfiguration_rate_;
    std::vector<HomogeneousIsland> islands_;
    ParallelIslandManager manager_;
};

#endif // PARALLEL_ISLAND_RUNNER_HPP