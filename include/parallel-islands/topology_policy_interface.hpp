#ifndef TOPOLOGY_POLICY_INTERFACE_HPP
#define TOPOLOGY_POLICY_INTERFACE_HPP
#include <vector>

using graph_t = std::vector<std::vector<int>>;

class TopologyPolicyInterface {
  public:
    TopologyPolicyInterface(size_t n_islands);
    virtual void configure_topology() = 0;

  protected:
    size_t n_islands_;
    graph_t topology_;
};

#endif