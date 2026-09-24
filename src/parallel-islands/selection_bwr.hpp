#ifndef SELECTION_BWR_HPP
#define SELECTION_BWR_HPP
#include "random/random_gen.hpp"
#include "selection_policy_interface.hpp"
#include <algorithm>
#include <tuple>

using std::tuple;
using std::vector;
/**
 * @brief Class that implements the selection policy for the parallel island model using
 * the BWR(Best, Worst, Random) strategy. Is selects three individuals from a population:
 * the best individual, the worst individual, and a random individual. These individuals
 * are then returned as migrants to be sent to other islands in the parallel island model.
 */
class SelectionBWR : public SelectionPolicyInterface {
  public:
    SelectionBWR() = default;
    virtual ~SelectionBWR() = default;
    virtual tuple<vector<vector<double>>, vector<double>> apply(const vector<vector<double>> &population,
                                                                vector<double> &fitness) override {
        vector<vector<double>> selected_individuals;
        vector<double> selected_fitness;

        // Sort the population and fitness based on fitness values
        std::vector<size_t> idx(population.size());
        std::iota(idx.begin(), idx.end(), 0);
        std::ranges::sort(idx, {}, [&](size_t i) { return fitness[i]; });
        std::vector<std::vector<double>> sorted_population;
        std::vector<double> sorted_fitness;

        for (auto i : idx) {
            sorted_population.push_back(std::move(population[i]));
            sorted_fitness.push_back(fitness[i]);
        }

        // get best solution
        selected_individuals.push_back(sorted_population.front());
        selected_fitness.push_back(sorted_fitness.front());
        // get worst solution
        selected_individuals.push_back(sorted_population.back());
        selected_fitness.push_back(sorted_fitness.back());
        // get random solution
        auto rnd_individual = random_gen::Rng().any(idx); // rnd individual index
        selected_individuals.push_back(sorted_population[rnd_individual]);
        selected_fitness.push_back(sorted_fitness[rnd_individual]);
        return std::make_tuple(selected_individuals, selected_fitness);
    }
};
#endif