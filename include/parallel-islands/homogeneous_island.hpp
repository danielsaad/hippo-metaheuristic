#ifndef HOMOGENEOUS_ISLAND_HPP
#define HOMOGENEOUS_ISLAND_HPP

#include "core/optimizer.hpp"
#include <memory>
#include <vector>

class HomogeneousIsland {
  public:
    HomogeneousIsland(std::unique_ptr<OptimizerBase> optimizer) : optimizer_(std::move(optimizer)) {};
    void run();
    void run(const std::vector<std::vector<double>> &migrated_solutions);
    void migrate_and_run(const std::vector<std::vector<double>> &migrated_solutions);

  public:
    std::unique_ptr<OptimizerBase> optimizer_;
};

#endif // HOMOGENEOUS_ISLAND_HPP