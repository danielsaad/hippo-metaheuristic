#include "hippo_math.h"
#include "hippo_random.h"
#include <cmath>
#include <numbers>
#include <random>

using std::tgamma;
using std::numbers::pi;

/**
 * @brief Generate a matrix of n Levy steps in m-dimension
 *
 * @param n number of levy steps
 * @param m  number of dimensions
 * @param beta
 * @return vvd matrix of levy steps
 */
vvd levy(size_t n, size_t m, double beta) {

    double num = tgamma(1 + beta) * sin(pi * beta / 2);
    double den = tgamma((1 + beta) / 2) * beta * pow(2, (beta - 1) / 2);
    double sigma_u = pow(num / den, 1 / beta);

    normal_dist nd_sdev(0, sigma_u);
    normal_dist nd;
    auto u_matrix = nd_sdev.generate_normal_dist_matrix(n, m);
    auto v_matrix = nd.generate_normal_dist_matrix(n, m);
    vvd z_matrix(n, std::vector<double>(m));

    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < m; j++) {
            z_matrix[i][j] = u_matrix[i][j] / (pow(fabs(v_matrix[i][j]), 1 / beta));
        }
    }

    return z_matrix;
}
