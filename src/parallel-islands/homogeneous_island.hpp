#ifndef HOMOGENEOUS_ISLAND_HPP
#define HOMOGENEOUS_ISLAND_HPP

#include "core/optimizer.hpp"
#include <memory>
#include <vector>

class HomogeneousIsland {
  public:
    HomogeneousIsland(std::unique_ptr<OptimizerBase> optimizer) : optimizer_(std::move(optimizer)) {};
    void run(bool initialize_flag = true);
    void set_optimizer(std::unique_ptr<OptimizerBase> new_optimizer);

  public:
    std::unique_ptr<OptimizerBase> optimizer_;
};

#endif // HOMOGENEOUS_ISLAND_HPP