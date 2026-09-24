#include "topology_complete_graph.hpp"

TopologyCompleteGraph::TopologyCompleteGraph(const vector<HomogeneousIsland> &islands)
    : TopologyPolicyInterface(islands) {
    configure_topology();
}
#include "topology_complete_graph.hpp"

void TopologyCompleteGraph::configure_topology() {
    graph_.clear();
    graph_.resize(n_islands_);
    for (size_t i = 0; i < n_islands_; ++i) {
        for (size_t j = i + 1; j < n_islands_; ++j) {
            graph_[i].push_back(j);
            graph_[j].push_back(i);
        }
    }
}
