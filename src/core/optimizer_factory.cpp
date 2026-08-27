#include "core/optimizer_factory.hpp"

#include "ho/hippo_optimizer.hpp"
#include "woa/woa.hpp"

std::unique_ptr<OptimizerBase>
OptimizerFactory::create(int type, size_t n_agents, size_t max_iterations,
                         std::unique_ptr<ProblemBase> objective_function) {
    switch (type) {
    case HO:
        return std::make_unique<HippoOptimizer>(n_agents, max_iterations, objective_function->clone());
    case WOA:
        return std::make_unique<Woa>(n_agents, max_iterations, objective_function->clone());
    default:
        return nullptr;
    }
}