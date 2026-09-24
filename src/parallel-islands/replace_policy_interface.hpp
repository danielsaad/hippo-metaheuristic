#ifndef REPLACE_POLICY_INTERFACE_HPP
#define REPLACE_POLICY_INTERFACE_HPP
#include "parallel-islands/homogeneous_island.hpp"

class ReplacePolicyInterface {
  public:
    ReplacePolicyInterface() = default;
    virtual ~ReplacePolicyInterface() = default;
    virtual void apply(HomogeneousIsland &island, const vector<vector<double>> &migrants,
                       const vector<double>& fitness) = 0;

  protected:
};

#endif