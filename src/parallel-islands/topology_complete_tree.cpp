#include "parallel-islands/topology_complete_tree.hpp"

TopologyCompleteTree::TopologyCompleteTree(size_t n_islands) : TopologyPolicyInterface(n_islands) {
    configure_topology();
}

void TopologyCompleteTree::configure_topology() {
    for (size_t i = 0; i < n_islands_; ++i) {
        size_t l = 2 * i + 1;   // left child
        size_t r = l + 1;       // right child
        size_t p = (i - 1) / 2; // parent
        if (i > 0) {
            topology_[i].push_back(p); // parent
        }
        if (l < n_islands_) {
            topology_[i].push_back(l); // left child
        }
        if (r < n_islands_) {
            topology_[i].push_back(r); // right child
        }
    }
}