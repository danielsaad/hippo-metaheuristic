#include "parallel_island_manager.hpp"

ParallelIslandManager::ParallelIslandManager(
    std::unique_ptr<TopologyPolicyInterface> topology_policy,
    std::unique_ptr<SelectionPolicyInterface> selection_policy,
    std::unique_ptr<ReplacePolicyInterface> replace_policy,
    std::unique_ptr<ReconfigurationPolicyInterface> reconfiguration_policy,
    std::unique_ptr<ReconfigurationChoicePolicy> reconfiguration_choice_policy)
    : _topology_policy(std::move(topology_policy)), _selection_policy(std::move(selection_policy)),
      _replace_policy(std::move(replace_policy)), _reconfiguration_policy(std::move(reconfiguration_policy)),
      _reconfiguration_choice_policy(std::move(reconfiguration_choice_policy)) {}

void
ParallelIslandManager::replace_individuals(HomogeneousIsland &island, const vector<vector<double>> &migrants,
                                           const vector<double> &fitness) {
    _replace_policy->apply(island, migrants, fitness);
}

bool
ParallelIslandManager::reconfigure_island(HomogeneousIsland &island,
                                          std::unique_ptr<OptimizerBase> new_optimizer) {
    return _reconfiguration_policy->apply(island, std::move(new_optimizer));
}

std::unique_ptr<OptimizerBase>
ParallelIslandManager::choose_optimizer_for_reconfiguration(const std::vector<HomogeneousIsland> &islands) {
    return _reconfiguration_choice_policy->apply(islands);
}

void
ParallelIslandManager::configure_topology() {
    _topology_policy->configure_topology();
}

vector<size_t>
ParallelIslandManager::get_neighbors(size_t u) {
    return _topology_policy->get_neighbors(u);
}
