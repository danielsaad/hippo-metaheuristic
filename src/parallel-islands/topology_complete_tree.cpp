#include "parallel-islands/topology_complete_tree.hpp"
#include "parallel-islands/homogeneous_island.hpp"

TopologyCompleteTree::TopologyCompleteTree(const vector<HomogeneousIsland> &islands)
    : TopologyPolicyInterface(islands) {
    configure_topology();
}

void TopologyCompleteTree::configure_topology() {
    graph_.clear();
    graph_.resize(n_islands_);
    for (size_t i = 0; i < n_islands_; ++i) {
        size_t l = 2 * i + 1;   // left child
        size_t r = l + 1;       // right child
        size_t p = (i - 1) / 2; // parent
        if(i > 0){
            // 0 does not have parent
            graph_[i].push_back(p); // parent
        }
        if (l < n_islands_) {
            graph_[i].push_back(l); // left child
        }
        if (r < n_islands_) {
            graph_[i].push_back(r); // right child
        }
    }
}