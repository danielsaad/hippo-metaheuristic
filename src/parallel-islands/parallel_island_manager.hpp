#ifndef PARALLEL_ISLAND_MANAGER_HPP
#define PARALLEL_ISLAND_MANAGER_HPP
#include "parallel-islands/replace_policy_interface.hpp"
#include "parallel-islands/selection_policy_interface.hpp"
#include "parallel-islands/topology_policy_interface.hpp"
#include <memory>

using std::tuple;
using std::vector;
class ManagerPolicy {
  public:
    ManagerPolicy() = default;
    ManagerPolicy(std::unique_ptr<TopologyPolicyInterface> topology_policy,
                  std::unique_ptr<ReplacePolicyInterface> replace_policy,
                  std::unique_ptr<SelectionPolicyInterface> selection_policy)
        : topology_policy(std::move(topology_policy)), selection_policy(std::move(selection_policy)),
          replace_policy(std::move(replace_policy)) {}

    virtual ~ManagerPolicy() = default;

    ManagerPolicy(const ManagerPolicy &) = delete;
    ManagerPolicy &operator=(const ManagerPolicy &) = delete;
    ManagerPolicy(ManagerPolicy &&) = default;
    ManagerPolicy &operator=(ManagerPolicy &&) = default;

  public:
    std::unique_ptr<TopologyPolicyInterface> topology_policy;
    std::unique_ptr<SelectionPolicyInterface> selection_policy;
    std::unique_ptr<ReplacePolicyInterface> replace_policy;
};
class ParallelIslandManager {
  public:
    ParallelIslandManager() = default;
    ParallelIslandManager(ManagerPolicy policy) : manager_(std::move(policy)) {}

    void set_manager_policy(ManagerPolicy policy) { manager_ = std::move(policy); }

    tuple<vector<vector<double>>, vector<double>> select_individuals(vector<vector<double>> &population,
                                                                     vector<double> &fitness) {
        return manager_.selection_policy->apply(population, fitness);
    }

    void replace_individuals(HomogeneousIsland &island, const vector<vector<double>> &migrants,
                             const vector<double> &fitness) {
        manager_.replace_policy->apply(island, migrants, fitness);
    }

    void configure_topology() { manager_.topology_policy->configure_topology(); }

    vector<size_t> get_neighbors(size_t u) { return manager_.topology_policy->get_neighbors(u); }

  private:
    ManagerPolicy manager_;
};

#endif