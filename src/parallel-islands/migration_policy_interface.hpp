#ifndef MIGRATION_POLICY_INTERFACE_HPP
#define MIGRATION_POLICY_INTERFACE_HPP
#include <vector>
#include <tuple>
class MigrationPolicyInterface {
  public:
    MigrationPolicyInterface(const std::vector<std::vector<double>> &population,
                             const std::vector<double> &fitness_)
        : population_(population), fitness_(fitness_) {}
    virtual ~MigrationPolicyInterface() = default;
    virtual std::tuple<std::vector<std::vector<double>>, std::vector<double>> apply() = 0;

  protected:
    const std::vector<std::vector<double>> &population_;
    const std::vector<double> &fitness_;
};
#endif