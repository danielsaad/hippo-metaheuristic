#ifndef RECONFIGURATION_POLICY_INTERFACE_HPP
#define RECONFIGURATION_POLICY_INTERFACE_HPP

#include "parallel-islands/homogeneous_island.hpp"

class ReconfigurationPolicyInterface {
  public:
    ReconfigurationPolicyInterface(std::vector<HomogeneousIsland> &islands) : islands_(islands) {};
    virtual ~ReconfigurationPolicyInterface() = default;
    virtual void
    apply() = 0;

  protected:
    std::vector<HomogeneousIsland> &islands_;
};

#endif