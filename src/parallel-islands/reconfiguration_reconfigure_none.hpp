#ifndef RECONFIGURATION_RECONFIGURE_NONE_HPP
#define RECONFIGURATION_RECONFIGURE_NONE_HPP
#include "reconfiguration_policy_interface.hpp"

class ReconfigurationReconfigureNone : public ReconfigurationPolicyInterface {
  public:
    ReconfigurationReconfigureNone(std::vector<HomogeneousIsland> &islands)
        : ReconfigurationPolicyInterface(islands) {};
    virtual ~ReconfigurationReconfigureNone() = default;

    void apply() override;
};
#endif
