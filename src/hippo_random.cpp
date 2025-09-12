
#include "hippo_random.h"
#include <algorithm>
#include <random>

std::mt19937 hippo_rng{std::random_device{}()};

// Definition of the module random generator

normal_dist::normal_dist(double mean, double udev) : m_mean(mean), m_udev(udev) {
    m_dist = std::normal_distribution<double>(m_mean, m_udev);
}

double normal_dist::generate() { return m_dist(hippo_rng); }

/**
 * @brief  Generate a matrix of n x m normal random variables
 *
 * @param n number of rows
 * @param m number of columns
 * @return vvd the matrix of normal random variables
 */
vvd normal_dist::generate_normal_dist_matrix(size_t n, size_t m) {
    vvd mat(n, std::vector<double>(m));
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < m; ++j) {
            mat[i][j] = m_dist(hippo_rng);
        }
    }
    return mat;
}

// Implementation for random_permutation
random_permutation::random_permutation(uint32_t n) : n(n) {}

std::vector<int> random_permutation::generate() {
    std::vector<int> perm(n);
    for (uint32_t i = 0; i < n; i++) {
        perm[i] = i;
    }
    std::shuffle(perm.begin(), perm.end(), hippo_rng);
    return perm;
}

std::vector<int> random_permutation::generate(int k) {
    std::vector<int> perm(n);
    for (uint32_t i = 0; i < n; i++) {
        perm[i] = i;
    }
    std::shuffle(perm.begin(), perm.end(), hippo_rng);
    perm.resize(k);
    return perm;
}