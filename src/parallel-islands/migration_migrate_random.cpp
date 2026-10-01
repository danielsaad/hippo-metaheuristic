#include "migration_migrate_random.hpp"
#include <numeric>
#include <random>
#include <algorithm>

std::tuple<std::vector<std::vector<double>>, std::vector<double>>
MigrateRandom::apply() {
    std::vector<std::vector<double>> migrants;
    std::vector<double> migrants_fitness;
    std::vector<size_t> indices(population_.size());
    std::iota(indices.begin(), indices.end(), 0);
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(indices.begin(), indices.end(), g);
    for (size_t i = 0; i < n_migrants_ && i < indices.size(); ++i) {
        size_t idx = indices[i];
        migrants.push_back(population_[idx]);
    }
    for (size_t i = 0; i < n_migrants_ && i < indices.size(); ++i) {
        size_t idx = indices[i];
        migrants_fitness.push_back(fitness_[idx]);
    }
    return std::make_tuple(migrants, migrants_fitness);
}