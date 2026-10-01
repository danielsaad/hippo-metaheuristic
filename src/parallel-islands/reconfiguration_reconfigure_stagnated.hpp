#ifndef RECONFIGURATION_RECONFIGURE_STAGNATED_HPP
#define RECONFIGURATION_RECONFIGURE_STAGNATED_HPP
#include "reconfiguration_policy_interface.hpp"

class ReconfigurationReconfigureStagnated : public ReconfigurationPolicyInterface {
  public:
    ReconfigurationReconfigureStagnated(std::vector<HomogeneousIsland> &islands)
        : ReconfigurationPolicyInterface(islands) {};
    virtual ~ReconfigurationReconfigureStagnated() = default;

    void
    apply() override;
};
#endif
