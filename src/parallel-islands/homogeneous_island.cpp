#include "parallel-islands/homogeneous_island.hpp"


void HomogeneousIsland::run() {
    optimizer_->run();
}

void HomogeneousIsland::migrate_and_run(const std::vector<std::vector<double>> &migrated_solutions) {
    optimizer_->migrate_and_run(migrated_solutions);
}

void HomogeneousIsland::run(const std::vector<std::vector<double>> &migrated_solutions) {
    optimizer_->migrate_and_run(migrated_solutions);
}