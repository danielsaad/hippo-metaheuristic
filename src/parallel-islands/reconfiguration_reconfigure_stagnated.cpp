#include "reconfiguration_reconfigure_stagnated.hpp"
#include "parallel-islands/homogeneous_island.hpp"
#include <algorithm>
#include <numeric>

bool
ReconfigurationReconfigureStagnated::apply(HomogeneousIsland &island,
                                           std::unique_ptr<OptimizerBase> new_optimizer) {
    const double EPS = 1e-2;
    const int n_last_generations = 5;
    if (island.convergence_curve_.size() < n_last_generations) {
        return false;
    }

    double fitness_mean = std::accumulate(island.convergence_curve_.end() - n_last_generations,
                                          island.convergence_curve_.end(), 0.0) /
                          n_last_generations;

    bool is_stagnated = 1.0 - (island.best_fitness_ / fitness_mean) < EPS;
    if (is_stagnated) {

        auto [population, fitness] = island.optimizer_->get_population_and_fitness();
        island.set_optimizer(std::move(new_optimizer));
        island.optimizer_->set_population_with_fitness(population, fitness);
    }
    return is_stagnated;
}
