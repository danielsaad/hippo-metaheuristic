#ifndef TOPOLOGY_POLICY_INTERFACE_HPP
#define TOPOLOGY_POLICY_INTERFACE_HPP
#include "parallel-islands/homogeneous_island.hpp"
#include <vector>
using std::pair;
using std::vector;

class TopologyPolicyInterface {
  public:
    TopologyPolicyInterface(const vector<HomogeneousIsland> &islands);
    virtual ~TopologyPolicyInterface() = default;
    virtual void configure_topology() = 0;

    vector<size_t> get_neighbors(size_t u) const;

  protected:
    size_t n_islands_;
    const vector<HomogeneousIsland> &islands_;
    std::vector<std::vector<size_t>> graph_;
};

#endif