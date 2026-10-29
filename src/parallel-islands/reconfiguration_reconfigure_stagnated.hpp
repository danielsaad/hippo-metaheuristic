#ifndef RECONFIGURATION_RECONFIGURE_STAGNATED_HPP
#define RECONFIGURATION_RECONFIGURE_STAGNATED_HPP
#include "reconfiguration_policy_interface.hpp"

class ReconfigurationReconfigureStagnated : public ReconfigurationPolicyInterface {
  public:
    ReconfigurationReconfigureStagnated() = default;
    virtual ~ReconfigurationReconfigureStagnated() = default;

    bool
    apply(HomogeneousIsland &island, std::unique_ptr<OptimizerBase> new_optimizer) override;
};
#endif
