
#ifndef RANDOM_GEN_H
#define RANDOM_GEN_H

#include <algorithm>
#include <random>

namespace random_gen {

/**
 * @brief  A simple random generator class that provides static methods for generating
 * random numbers, vectors, and matrices.
 *
 */
class Rng {
  private:
    std::mt19937 rng;

  public:
    Rng() : Rng(std::random_device{}()) {}
    Rng(uint32_t seed) : rng(seed) {}

    /**
     * @brief  Generate a value from the given distribution.
     *
     * @tparam Dist The distribution type, e.g., std::uniform_real_distribution<double>
     * @param dist The distribution object
     * @return auto A random value generated from the distribution.
     */
    template <typename Dist> auto rnd(Dist &dist) { return dist(rng); }

    /**
     * @brief  Generate a vector of random values from the given distribution.
     *
     * @tparam T The type of the elements in the vector.
     * @tparam Dist The distribution type, e.g., std::uniform_real_distribution<double>
     * @param n The number of elements in the vector.
     * @param dist The distribution object.
     * @return std::vector<T> A vector of random values generated from the distribution.
     */
    template <typename T, typename Dist> std::vector<T> vector(size_t n, Dist &dist) {
        std::vector<T> v(n);
        for (auto &x : v)
            x = dist(rng);
        return v;
    }
    /**
     * @brief  Generate a matrix of random values from the given distribution.
     *
     * @tparam T The type of the elements in the matrix.
     * @tparam Dist The distribution type, e.g., std::uniform_real_distribution<double>
     * @param n The number of rows in the matrix.
     * @param m The number of columns in the matrix.
     * @param dist The distribution object.
     * @return std::vector<std::vector<T>> A matrix of random values generated from the distribution.
     */
    template <typename T, typename Dist> std::vector<std::vector<T>> matrix(size_t n, size_t m, Dist &dist) {
        std::vector<std::vector<T>> matrix(n);
        for (auto &row : matrix) {
            row = vector<T>(m, dist);
        }
        return matrix;
    }
};

} // namespace random_gen
#endif // RANDOM_GEN_H