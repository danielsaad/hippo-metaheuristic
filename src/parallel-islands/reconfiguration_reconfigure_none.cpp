#include "reconfiguration_reconfigure_none.hpp"
#include "core/optimizer.hpp"
#include "parallel-islands/homogeneous_island.hpp"
#include <memory>

bool
ReconfigurationReconfigureNone::apply([[maybe_unused]] HomogeneousIsland &island,
                                      [[maybe_unused]] std::unique_ptr<OptimizerBase> ptr) {
    return false;
}
