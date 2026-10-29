#ifndef PARALLEL_ISLAND_MANAGER_HPP
#define PARALLEL_ISLAND_MANAGER_HPP
#include "core/optimizer.hpp"
#include "parallel-islands/homogeneous_island.hpp"
#include "parallel-islands/reconfiguration_choice_policy.hpp"
#include "parallel-islands/reconfiguration_policy_interface.hpp"
#include "parallel-islands/replace_policy_interface.hpp"
#include "parallel-islands/selection_policy_interface.hpp"
#include "parallel-islands/topology_policy_interface.hpp"
#include <memory>

using std::tuple;
using std::vector;

class ParallelIslandManager {
  public:
    ParallelIslandManager() = default;

    /**
     * @brief Construct a new Parallel Island Manager object
     *
     * @param topology_policy The topology policy to be used for the islands.
     * @param selection_policy  The selection policy to be used for selecting individuals
     * from the islands.
     * @param replace_policy  The replace policy to be used for replacing individuals in
     * the islands.
     * @param reconfiguration_policy  The reconfiguration policy to be used for
     * reconfiguring the islands.
     * @param reconfiguration_choice_policy  The reconfiguration choice policy to be used
     * for choosing the optimizer for reconfiguration.
     */
    ParallelIslandManager(std::unique_ptr<TopologyPolicyInterface> topology_policy,
                          std::unique_ptr<SelectionPolicyInterface> selection_policy,
                          std::unique_ptr<ReplacePolicyInterface> replace_policy,
                          std::unique_ptr<ReconfigurationPolicyInterface> reconfiguration_policy,
                          std::unique_ptr<ReconfigurationChoicePolicy> reconfiguration_choice_policy);

    /**
     * @brief Select individuals from the population in order to be migrated.
     *
     * @param population The population of the island.
     * @param fitness The fitness values of the population.
     * @return tuple<vector<vector<double>>, vector<double>> The selected individuals and
     * their fitness values.
     */
    tuple<vector<vector<double>>, vector<double>>
    select_individuals(vector<vector<double>> &population, vector<double> &fitness) {
        return _selection_policy->apply(population, fitness);
    }

    /**
     * @brief Replace individuals in the island with the selected individuals.
     *
     * @param island The island in which to replace individuals.
     * @param migrants The selected individuals to be migrated.
     * @param fitness The fitness values of the selected individuals.
     */
    void
    replace_individuals(HomogeneousIsland &island, const vector<vector<double>> &migrants,
                        const vector<double> &fitness);

    /**
     * @brief Reconfigure the island with a new optimizer.
     *
     * @param island Reconfigure a island with a new optimizer based on the
     * reconfiguration policy.
     * @param new_optimizer The chosen optimizer for reconfiguration based on the
     * reconfiguration choice policy.
     * @return bool True if the island was reconfigured, false otherwise.
     */
    bool
    reconfigure_island(HomogeneousIsland &island, std::unique_ptr<OptimizerBase> new_optimizer);

    /**
     * @brief Chose best optimizer for reconfiguration based on some criteria (e.g., best
     * fitness, diversity, etc.)
     *
     * @param islands The islands to choose from.
     * @return std::unique_ptr<OptimizerBase> The optimizer to be used for reconfiguration.
     */
    std::unique_ptr<OptimizerBase>
    choose_optimizer_for_reconfiguration(const std::vector<HomogeneousIsland> &islands);

    /**
     * @brief Configure the topology of the islands.
     */
    void
    configure_topology();

    /**
     * @brief Get the neighbors object
     *
     * @param u
     * @return vector<size_t>
     */
    vector<size_t>
    get_neighbors(size_t u);

  private:
    std::unique_ptr<TopologyPolicyInterface> _topology_policy;
    std::unique_ptr<SelectionPolicyInterface> _selection_policy;
    std::unique_ptr<ReplacePolicyInterface> _replace_policy;
    std::unique_ptr<ReconfigurationPolicyInterface> _reconfiguration_policy;
    std::unique_ptr<ReconfigurationChoicePolicy> _reconfiguration_choice_policy;
};

#endif