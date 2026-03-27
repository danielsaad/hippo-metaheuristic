#ifndef VECTOR_OPERATIONS_H
#define VECTOR_OPERATIONS_H
#include "linear_algebra/vector.hpp"
#include <cassert>

namespace linear_algebra {
/**
 * @brief Adds two vectors element-wise
 *
 * @tparam T Type.
 * @param a First vector.
 * @param b Second vector.
 * @return VectorT<T> The result of a + b.
 */
template <class T> VectorT<T> operator+(const VectorT<T> &a, const VectorT<T> &b) {
    const size_t n = a.get_data().size();
    VectorT<T> result(n);
    const auto &v1 = a.get_data();
    const auto &v2 = b.get_data();
    auto &ans = result.get_data();
    assert(v1.size() == v2.size());
    for (size_t i = 0; i < n; i++) {
        ans[i] = v1[i] + v2[i];
    }
    return result;
}

/**
 * @brief Adds a scalar to each vector element
 *
 * @tparam T Type.
 * @param a Vector.
 * @param scalar Scalar value.
 * @return VectorT<T> The result of a + scalar.
 */
template <class T> VectorT<T> operator+(const VectorT<T> &a, const T &scalar) {
    const size_t n = a.get_data().size();
    VectorT<T> result(n);
    const auto &v1 = a.get_data();
    auto &ans = result.get_data();
    assert(v1.size() == ans.size());
    for (size_t i = 0; i < n; i++) {
        ans[i] = v1[i] + scalar;
    }
    return result;
}

/**
 * @brief Adds each vector element to a scalar
 *
 * @tparam T Type.
 * @param scalar Scalar value.
 * @param a Vector.
 * @return VectorT<T> The result of scalar + a.
 */
template <class T> VectorT<T> operator+(const T &scalar, const VectorT<T> &a) { return a + scalar; }

/**
 * @brief Subtracts two vectors element-wise
 *
 * @tparam T Type.
 * @param a First vector.
 * @param b Second vector.
 * @return VectorT<T> The result of a - b.
 */
template <class T> VectorT<T> operator-(const VectorT<T> &a, const VectorT<T> &b) {
    const size_t n = a.get_data().size();
    VectorT<T> result(n);
    const auto &v1 = a.get_data();
    const auto &v2 = b.get_data();
    auto &ans = result.get_data();
    assert(v1.size() == v2.size());
    for (size_t i = 0; i < n; i++) {
        ans[i] = v1[i] - v2[i];
    }
    return result;
}

/**
 * @brief Subtracts a scalar from each vector element
 *
 * @tparam T Type.
 * @param a Vector.
 * @param scalar Scalar value.
 * @return VectorT<T> The result of a - scalar.
 */
template <class T> VectorT<T> operator-(const VectorT<T> &a, const T &scalar) {
    const size_t n = a.get_data().size();
    VectorT<T> result(n);
    const auto &v1 = a.get_data();
    auto &ans = result.get_data();
    assert(v1.size() == ans.size());
    for (size_t i = 0; i < n; i++) {
        ans[i] = v1[i] - scalar;
    }
    return result;
}

/**
 * @brief Subtracts each vector element from a scalar
 *
 * @tparam T Type.
 * @param scalar Scalar value.
 * @param a Vector.
 * @return VectorT<T> The result of scalar - a.
 */
template <class T> VectorT<T> operator-(const T &scalar, const VectorT<T> &a) {
    const size_t n = a.get_data().size();
    VectorT<T> result(n);
    const auto &v1 = a.get_data();
    auto &ans = result.get_data();
    assert(v1.size() == ans.size());
    for (size_t i = 0; i < n; i++) {
        ans[i] = scalar - v1[i];
    }
    return result;
}

/**
 * @brief Multiplies two vectors element-wise
 *
 * @tparam T Type.
 * @param a First vector.
 * @param b Second vector.
 * @return VectorT<T> The result of a .* b.
 */

template <class T> VectorT<T> operator*(const VectorT<T> &a, const VectorT<T> &b) {
    const size_t n = a.get_data().size();
    VectorT<T> result(n);
    const auto &v1 = a.get_data();
    const auto &v2 = b.get_data();
    auto &ans = result.get_data();
    assert(v1.size() == v2.size());
    for (size_t i = 0; i < n; i++) {
        ans[i] = v1[i] * v2[i];
    }
    return result;
}

/**
 * @brief Multiplies a vector by a scalar
 *
 * @tparam T Type.
 * @param a Vector.
 * @param scalar Scalar value.
 * @return VectorT<T> The result of a * scalar.
 */
template <class T> VectorT<T> operator*(const VectorT<T> &a, const T &scalar) {
    const size_t n = a.get_data().size();
    VectorT<T> result(n);
    const auto &v1 = a.get_data();
    auto &ans = result.get_data();
    assert(v1.size() == ans.size());
    for (size_t i = 0; i < n; i++) {
        ans[i] = v1[i] * scalar;
    }
    return result;
}

/**
 * @brief Adds b to a element-wise in-place
 *
 * @tparam T Type.
 * @param a Vector to be modified.
 * @param b Vector to be added to a.
 * @return VectorT<T>& The modified vector.
 */
template <class T> VectorT<T> &operator+=(VectorT<T> &a, const VectorT<T> &b) {
    auto &v1 = a.get_data();
    const auto &v2 = b.get_data();
    assert(v1.size() == v2.size());
    const size_t n = v1.size();
    for (size_t i = 0; i < n; i++) {
        v1[i] += v2[i];
    }
    return a;
}

/**
 * @brief Adds a scalar to each vector element in-place
 *
 * @tparam T Type.
 * @param a Vector to be modified.
 * @param scalar Scalar value.
 * @return VectorT<T>& The modified vector.
 */
template <class T> VectorT<T> &operator+=(VectorT<T> &a, const T &scalar) {
    auto &v1 = a.get_data();
    const size_t n = v1.size();
    for (size_t i = 0; i < n; i++) {
        v1[i] += scalar;
    }
    return a;
}

/**
 * @brief Subtracts b from a element-wise in-place
 *
 * @tparam T Type.
 * @param a Vector to be modified.
 * @param b Vector to be subtracted from a.
 * @return VectorT<T>& The modified vector.
 */
template <class T> VectorT<T> &operator-=(VectorT<T> &a, const VectorT<T> &b) {
    auto &v1 = a.get_data();
    const auto &v2 = b.get_data();
    assert(v1.size() == v2.size());
    const size_t n = v1.size();
    for (size_t i = 0; i < n; i++) {
        v1[i] -= v2[i];
    }
    return a;
}

/**
 * @brief Subtracts a scalar from each vector element in-place
 *
 * @tparam T Type.
 * @param a Vector to be modified.
 * @param scalar Scalar value.
 * @return VectorT<T>& The modified vector.
 */
template <class T> VectorT<T> &operator-=(VectorT<T> &a, const T &scalar) {
    auto &v1 = a.get_data();
    const size_t n = v1.size();
    for (size_t i = 0; i < n; i++) {
        v1[i] -= scalar;
    }
    return a;
}

/**
 * @brief Multiplies a by b element-wise in-place
 *
 * @tparam T Type.
 * @param a Vector to be modified.
 * @param b Vector to be multiplied with a.
 * @return VectorT<T>& The modified vector.
 */
template <class T> VectorT<T> &operator*=(VectorT<T> &a, const VectorT<T> &b) {
    auto &v1 = a.get_data();
    const auto &v2 = b.get_data();
    assert(v1.size() == v2.size());
    const size_t n = v1.size();
    for (size_t i = 0; i < n; i++) {
        v1[i] *= v2[i];
    }
    return a;
}

/**
 * @brief Multiplies a by a scalar in-place
 *
 * @tparam T Type.
 * @param a Vector to be modified.
 * @param scalar Scalar value.
 * @return VectorT<T>& The modified vector.
 */
template <class T> VectorT<T> &operator*=(VectorT<T> &a, const T &scalar) {
    auto &v1 = a.get_data();
    const size_t n = v1.size();
    for (size_t i = 0; i < n; i++) {
        v1[i] *= scalar;
    }
    return a;
}
} // namespace linear_algebra
#endif
