#include "reconfiguration_choice_best.hpp"

std::unique_ptr<OptimizerBase>
ReconfigurationChoiceBest::apply(const vector<HomogeneousIsland> &islands) {
    if (islands.empty()) {
        return nullptr;
    }
    const HomogeneousIsland *best_island = &islands[0];
    for (size_t i = 1; i < islands.size(); i++) {
        if (islands[i].best_fitness_ < best_island->best_fitness_) {
            best_island = &islands[i];
        }
    }

    return best_island->optimizer_->clone();
}