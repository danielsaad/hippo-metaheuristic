#ifndef TOPOLOGY_COMPLETE_TREE_HPP
#define TOPOLOGY_COMPLETE_TREE_HPP
#include "parallel-islands/topology_policy_interface.hpp"

class TopologyCompleteTree : public TopologyPolicyInterface {
  public:
    TopologyCompleteTree(size_t n_islands);
    void configure_topology() override;
};

#endif