
#ifndef HIPPO_RANDOM_H
#define HIPPO_RANDOM_H

#include <algorithm>
#include <random>

extern std::mt19937 hippo_rng;

using vvd = std::vector<std::vector<double>>;
/**
 * @brief  Implements the normal distribution generator
 */
class normal_dist {
  public:
    normal_dist(double mean = 0.0, double udev = 1.0);
    double generate();
    vvd generate_normal_dist_matrix(size_t n, size_t m);

  private:
    std::normal_distribution<double> m_dist;
    double m_mean, m_udev;
};

/**
 * @brief  Implements the uniform distribution generator
 */
template <class T> class uniform_dist {
  public:
    using dist_type = typename std::conditional<std::is_integral<T>::value, std::uniform_int_distribution<T>,
                                                std::uniform_real_distribution<T>>::type;

    uniform_dist(T lb, T ub);
    T generate();
    std::vector<T> generate_uniform_dist_vector(size_t n);
    std::vector<std::vector<T>> generate_uniform_dist_matrix(size_t n, size_t m);

  private:
    dist_type m_dist;
    T lb, ub;
};

template <class T> uniform_dist<T>::uniform_dist(T lb, T ub) : lb(lb), ub(ub) { m_dist = dist_type(lb, ub); }

template <class T> T uniform_dist<T>::generate() { return m_dist(hippo_rng); }

template <class T> std::vector<T> uniform_dist<T>::generate_uniform_dist_vector(size_t n) {
    std::vector<T> v(n);
    for (auto &x : v) {
        x = m_dist(hippo_rng);
    }
    return v;
}

template <class T>
std::vector<std::vector<T>> uniform_dist<T>::generate_uniform_dist_matrix(size_t n, size_t m) {
    std::vector<std::vector<T>> mat(n, std::vector<T>(m));
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < m; ++j) {
            mat[i][j] = m_dist(hippo_rng);
        }
    }
    return mat;
}

class random_permutation {

  public:
    random_permutation(uint32_t n);
    std::vector<int> generate();
    std::vector<int> generate(int k);

  private:
    uint32_t n;
};

#endif // HIPPO_RANDOM_H