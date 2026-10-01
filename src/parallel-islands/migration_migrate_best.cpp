#include "migration_migrate_best.hpp"
#include <algorithm>
#include <numeric>

std::tuple<std::vector<std::vector<double>>, std::vector<double>>
MigrateBest::apply() {
    std::vector<std::vector<double>> migrants;
    std::vector<double> migrants_fitness;
    std::vector<size_t> indices(population_.size());
    std::iota(indices.begin(), indices.end(), 0);
    std::sort(indices.begin(), indices.end(),
              [this](size_t a, size_t b) { return fitness_[a] < fitness_[b]; });
    for (size_t i = 0; i < n_migrants_ && i < indices.size(); ++i) {
        size_t idx = indices[i];
        migrants.push_back(population_[idx]);
        migrants_fitness.push_back(fitness_[idx]);
    }
    return std::make_tuple(migrants, migrants_fitness);
}