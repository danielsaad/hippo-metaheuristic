#include "parallel-islands/topology_policy_interface.hpp"

TopologyPolicyInterface::TopologyPolicyInterface(const vector<HomogeneousIsland> &islands)
    : n_islands_(islands.size()), islands_(islands) {}

vector<size_t> TopologyPolicyInterface::get_neighbors(size_t u) const { return graph_[u]; };