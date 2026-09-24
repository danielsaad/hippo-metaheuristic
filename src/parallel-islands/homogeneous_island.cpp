#include "parallel-islands/homogeneous_island.hpp"

void HomogeneousIsland::set_optimizer(std::unique_ptr<OptimizerBase> new_optimizer) {
    optimizer_ = std::move(new_optimizer);
}

void HomogeneousIsland::run(bool initialize_flag) { optimizer_->run(initialize_flag); }