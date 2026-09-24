#ifndef REPLACE_WORST_HPP
#define REPLACE_WORST_HPP
#include "parallel-islands/replace_policy_interface.hpp"
#include <algorithm>
#include <numeric>
/**
 * @brief The ReplaceWorst class implements the replace policy for the parallel island model.
 * It replaces the worst individuals in the island with the incoming migrants.
 */
class ReplaceWorst : public ReplacePolicyInterface {
  public:
    ReplaceWorst() = default;
    virtual void apply(HomogeneousIsland &island, const vector<vector<double>> &migrants,
                       const vector<double> &fitness) override {
        auto [p, f] = island.optimizer_->get_population_and_fitness();
        // Sort population and fitness based on fitness values
        std::vector<size_t> idx(p.size());
        std::iota(idx.begin(), idx.end(), 0);

        std::ranges::sort(idx, {}, [&](size_t i) { return f[i]; });

        std::vector<std::vector<double>> new_population;
        std::vector<double> new_fitness;

        for (auto i : idx) {
            new_population.push_back(std::move(p[i]));
            new_fitness.push_back(f[i]);
        }
        p = std::move(new_population);
        f = std::move(new_fitness);
        // Replace the worst individuals with the migrants
        for (size_t i = 0; i < migrants.size(); ++i) {
            p[p.size() - 1 - i] = migrants[i];
            f[f.size() - 1 - i] = fitness[i];
        }
        // Update the island's population and fitness
        island.optimizer_->set_population_with_fitness(p, f);
    }
};

#endif