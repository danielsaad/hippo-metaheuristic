#include "parallel-islands/topology_complete_graph.hpp"

TopologyCompleteGraph::TopologyCompleteGraph(size_t n_islands) : TopologyPolicyInterface(n_islands) {
    configure_topology();
}

void TopologyCompleteGraph::configure_topology() {
    for (size_t i = 0; i < n_islands_; ++i) {
        for (size_t j = 0; j < n_islands_; ++j) {
            if (i != j) {
                topology_[i].push_back(j);
            }
        }
    }
}