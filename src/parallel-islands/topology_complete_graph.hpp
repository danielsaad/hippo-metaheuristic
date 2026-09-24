#ifndef TOPOLOGY_COMPLETE_GRAPH_HPP
#define TOPOLOGY_COMPLETE_GRAPH_HPP
#include "parallel-islands/topology_policy_interface.hpp"

class TopologyCompleteGraph : public TopologyPolicyInterface {
  public:
    TopologyCompleteGraph(const vector<HomogeneousIsland> &islands);
    void configure_topology() override;
};

#endif