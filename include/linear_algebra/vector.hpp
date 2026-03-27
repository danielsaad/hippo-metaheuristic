#ifndef VECTOR_H
#define VECTOR_H
#include <vector>
namespace linear_algebra {
template <class T> class VectorT {
  public:
    VectorT(size_t n) { data = std::vector<T>(n, 0); }
    VectorT(std::initializer_list<T> init) : data(init) {}
    std::vector<T> &get_data() { return data; }
    const std::vector<T> &get_data() const { return data; }

  private:
    std::vector<T> data;
};
} // namespace linear_algebra
#endif