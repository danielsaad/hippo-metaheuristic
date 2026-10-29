#ifndef RECONFIGURATION_CHOICE_POLICY_HPP
#define RECONFIGURATION_CHOICE_POLICY_HPP
#include "core/optimizer.hpp"
#include "homogeneous_island.hpp"

class ReconfigurationChoicePolicy {
  public:
    ReconfigurationChoicePolicy() = default;
    virtual ~ReconfigurationChoicePolicy() = default;
    virtual std::unique_ptr<OptimizerBase>
    apply(const vector<HomogeneousIsland> &islands) = 0;
};

#endif