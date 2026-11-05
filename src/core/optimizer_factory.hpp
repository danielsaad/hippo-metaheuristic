#ifndef OPTIMIZER_FACTORY_HPP
#define OPTIMIZER_FACTORY_HPP

#include "core/optimizer.hpp"
#include "core/problem.hpp"

#include <memory>

enum {
    HO = 1,
    WOA,
    GWO,
    OPTIMIZER_FACTORY_SIZE = GWO
};

class OptimizerFactory {
  public:
    static std::unique_ptr<OptimizerBase> create(int type, size_t n_agents, size_t max_iterations,
                                                 std::unique_ptr<ProblemBase> objective_function);
};

#endif