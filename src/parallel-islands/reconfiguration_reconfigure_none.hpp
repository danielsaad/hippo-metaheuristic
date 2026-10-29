#ifndef RECONFIGURATION_RECONFIGURE_NONE_HPP
#define RECONFIGURATION_RECONFIGURE_NONE_HPP
#include "reconfiguration_policy_interface.hpp"

class ReconfigurationReconfigureNone : public ReconfigurationPolicyInterface {
  public:
    ReconfigurationReconfigureNone() = default;
    virtual ~ReconfigurationReconfigureNone() = default;

  public:
    bool
    apply(HomogeneousIsland &island, std::unique_ptr<OptimizerBase> new_optimizer) override;
};
#endif
