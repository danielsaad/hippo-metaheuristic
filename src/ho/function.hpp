#ifndef FUNCTION_H
#define FUNCTION_H

#include <functional>
#include <vector>

using std::vector;
using vvd = vector<vector<double>>;
using vd = vector<double>;
using fun = std::function<double(const vd &)>;
using fun2d = std::function<double(const vvd &)>;

#endif // FUNCTION_H