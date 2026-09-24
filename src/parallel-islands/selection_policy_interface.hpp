#ifndef SELECTION_POLICY_INTERFACE_HPP
#define SELECTION_POLICY_INTERFACE_HPP

#include "homogeneous_island.hpp"
#include <tuple>
#include <vector>

using std::tuple;
using std::vector;

class SelectionPolicyInterface {
  public:
    SelectionPolicyInterface() = default;
    virtual ~SelectionPolicyInterface() = default;
    virtual tuple<vector<vector<double>>, vector<double>> apply(const vector<vector<double>> &population,
                                                                vector<double> &fitness) = 0;
};

#endif // SELECTION_POLICY_INTERFACE_HPP