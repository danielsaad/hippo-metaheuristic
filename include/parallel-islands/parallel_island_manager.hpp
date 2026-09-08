#ifndef PARALLEL_ISLAND_MANAGER_HPP
#define PARALLEL_ISLAND_MANAGER_HPP
#include <memory>

class ParallelIslandManager {
  public:
    ParallelIslandManager() = default;

    void reconfigure_migration(std::unique_ptr<MigrationPolicyInterface> migration_policy) {
        migration_policy_ = std::move(migration_policy);
    }

    void reconfigure_topology(std::unique_ptr<TopologyPolicyInterface> topology_policy) {
        topology_policy_ = std::move(topology_policy);
    }

    std::unique_ptr<TopologyPolicyInterface> topology_policy_;
    std::unique_ptr<MigrationPolicyInterface> migration_policy_;
};

#endif