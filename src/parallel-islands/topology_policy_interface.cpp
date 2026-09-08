#include "parallel-islands/topology_policy_interface.hpp"

TopologyPolicyInterface::TopologyPolicyInterface(size_t n_islands)
    : n_islands_(n_islands), topology_(n_islands) {}