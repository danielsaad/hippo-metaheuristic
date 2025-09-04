#ifndef HIPPO_MATH_H
#define HIPPO_MATH_H

#include <cstdlib>
#include <vector>

using vvd = std::vector<std::vector<double>>;

vvd levy(size_t n, size_t m, double beta);

vvd filter(const vvd &population, const std::vector<int> &idx) {
    vvd filtered_population;
    for (const auto &i : idx) {
        filtered_population.emplace_back(population[i]);
    }
    return filtered_population;
}

#endif // HIPPO_MATH_H