#ifndef HIPPO_MATH_H
#define HIPPO_MATH_H

#include <cstdlib>
#include <vector>

using vvd = std::vector<std::vector<double>>;

vvd levy(size_t n, size_t m, double beta);

vvd filter(const vvd &population, const std::vector<int> &idx);

#endif // HIPPO_MATH_H