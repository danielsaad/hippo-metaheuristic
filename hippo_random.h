
#ifndef HIPPO_RANDOM_H
#define HIPPO_RANDOM_H

#include <algorithm>
#include <random>

using vvd = std::vector<std::vector<double>>;
/**
 * @brief  Implements the normal distribution generator
 */
class normal_dist {
  public:
    normal_dist(double mean = 0.0, double udev = 1.0) : m_mean(mean), m_udev(udev) {
        m_gen = std::mt19937(std::random_device{}());
        m_dist = std::normal_distribution<double>(m_mean, m_udev);
    }

    double generate(){
        return m_dist(m_gen);
    }
    /**
     * @brief  Generate a matrix of n x m normal random variables
     *
     * @param n number of rows
     * @param m number of columns
     * @return vvd the matrix of normal random variables
     */
    vvd generate_normal_dist_matrix(size_t n, size_t m) {
        vvd mat(n, std::vector<double>(m));
        for (size_t i = 0; i < n; ++i) {
            for (size_t j = 0; j < m; ++j) {
                mat[i][j] = m_dist(m_gen);
            }
        }
        return mat;
    }

  private:
    static std::mt19937 m_gen = std::mt19937(std::random_device{}());
    std::normal_distribution<double> m_dist;
    double m_mean, m_udev;
};

/**
 * @brief  Implements the uniform distribution generator
 *
 */
template <class T> class uniform_dist {
  public:
    using dist_type = typename std::conditional<std::is_integral<T>::value, std::uniform_int_distribution<T>,
                                                std::uniform_real_distribution<T>>::type;

    /**
     * @brief Construct a new uniform dist object. If T is real, then
     * the considered interval is [lb,ub). If T is integer, then the considered
     * interval is [lb,ub]
     *
     * @param lb  the lower bound
     * @param ub  the upper bound
     */
    uniform_dist(T lb, T ub) : lb(lb), ub(ub) { m_dist = dist_type(lb, ub); }

    T generate() { return m_dist(m_gen); }
    /**
     * @brief  Generate a vector of n uniform random variables
     *
     * @param n number of values
     * @return The vector of uniform random variables
     */
    std::vector<T> generate_uniform_dist_vector(size_t n) {
        std::vector<T> v(n);
        for (auto &x : v) {
            x = m_dist(m_gen);
        }
        return v;
    }
    /**
     * @brief  Generate a matrix of n x m uniform random variables
     *
     * @param n number of rows
     * @param m number of columns
     * @return The matrix of uniform random variables
     */
    std::vector<std::vector<T>> generate_uniform_dist_matrix(size_t n, size_t m) {
        std::vector<std::vector<T>> mat(n, std::vector<T>(m));
        for (size_t i = 0; i < n; ++i) {
            for (size_t j = 0; j < m; ++j) {
                mat[i][j] = m_dist(m_gen);
            }
        }
        return mat;
    }

  private:
    static std::mt19937 m_gen = std::mt19937(std::random_device{}());
    dist_type m_dist;
    T lb, ub;
};

class random_permutation {
  public:
    random_permutation(uint32_t n) : n(n), m_gen(std::random_device{}()) {}
    std::vector<int> generate() {
        std::vector<int> perm(n);
        for (uint32_t i = 0; i < n; i++) {
            perm[i] = i;
        }
        std::shuffle(perm.begin(), perm.end(), m_gen);
        return perm;
    }

    std::vector<int> generate(int k) {
        std::vector<int> perm(n);
        for (uint32_t i = 0; i < n; i++) {
            perm[i] = i;
        }
        std::shuffle(perm.begin(), perm.end(), m_gen);
        perm.resize(k);
        return perm;
    }

  private:
    uint32_t n;
    std::mt19937 m_gen;
};

#endif // HIPPO_RANDOM_H