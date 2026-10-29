#ifndef RECONFIGURATION_POLICY_INTERFACE_HPP
#define RECONFIGURATION_POLICY_INTERFACE_HPP

#include "parallel-islands/homogeneous_island.hpp"

class ReconfigurationPolicyInterface {
  public:
    ReconfigurationPolicyInterface() = default;
    virtual ~ReconfigurationPolicyInterface() = default;
    virtual bool
    apply(HomogeneousIsland &island, std::unique_ptr<OptimizerBase> new_optimizer) = 0;

  protected:
};

#endif