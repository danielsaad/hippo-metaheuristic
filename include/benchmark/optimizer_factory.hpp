#ifndef OPTIMIZER_FACTORY_HPP
#define OPTIMIZER_FACTORY_HPP
#include "ho/hippo_optimizer.hpp"
#include "woa/woa.hpp"
#include <memory>

enum {
    HO = 1,
    WOA,
};

class OptimizerFactory {
  public:
    static std::unique_ptr<OptimizerBase> create(int type, size_t n_agents, size_t max_iterations,
                                                      std::unique_ptr<ProblemBase> objective_function);
};

#endif
