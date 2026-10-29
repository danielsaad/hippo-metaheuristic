#ifndef RECONFIGURATION_CHOICE_BEST_HPP
#define RECONFIGURATION_CHOICE_BEST_HPP
#include "reconfiguration_choice_policy.hpp"

/**
 * @brief  Select the optimizer from the islands based on the best fitness value.
 */

class ReconfigurationChoiceBest : public ReconfigurationChoicePolicy {
  public:
    ReconfigurationChoiceBest() = default;
    virtual ~ReconfigurationChoiceBest() = default;
    std::unique_ptr<OptimizerBase>
    apply(const vector<HomogeneousIsland> &islands) override;
};

#endif