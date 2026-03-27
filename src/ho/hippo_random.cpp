
#include "ho/hippo_random.hpp"
#include <algorithm>
#include <random>

std::mt19937 hippo_rng{std::random_device{}()};

// Definition of the module random generator

NormalDist::NormalDist(double mean, double udev) : m_mean(mean), m_udev(udev) {
    m_dist = std::normal_distribution<double>(m_mean, m_udev);
}

double NormalDist::generate() { return m_dist(hippo_rng); }

/**
 * @brief  Generate a matrix of n x m normal random variables
 *
 * @param n number of rows
 * @param m number of columns
 * @return vvd the matrix of normal random variables
 */
vvd NormalDist::generate_normal_dist_matrix(size_t n, size_t m) {
    vvd mat(n, std::vector<double>(m));
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < m; ++j) {
            mat[i][j] = m_dist(hippo_rng);
        }
    }
    return mat;
}

// Implementation for RandomPermutation
RandomPermutation::RandomPermutation(uint32_t n) : n(n) {}

std::vector<int> RandomPermutation::generate() {
    std::vector<int> perm(n);
    for (uint32_t i = 0; i < n; i++) {
        perm[i] = i;
    }
    std::shuffle(perm.begin(), perm.end(), hippo_rng);
    return perm;
}

std::vector<int> RandomPermutation::generate(int k) {
    std::vector<int> perm(n);
    for (uint32_t i = 0; i < n; i++) {
        perm[i] = i;
    }
    std::shuffle(perm.begin(), perm.end(), hippo_rng);
    perm.resize(k);
    return perm;
}