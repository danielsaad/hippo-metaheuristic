#ifndef MIGRATION_MIGRATE_NONE_HPP
#define MIGRATION_MIGRATE_NONE_HPP
#include "migration_policy_interface.hpp"
class MigrateNone : public MigrationPolicyInterface {
  public:
    MigrateNone(const std::vector<std::vector<double>> &population, const std::vector<double> &fitness_values)
        : MigrationPolicyInterface(population, fitness_values) {}
    virtual ~MigrateNone() = default;
    virtual std::tuple<std::vector<std::vector<double>>, std::vector<double>>
    apply() override;
};
#endif