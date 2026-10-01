#ifndef MIGRATION_MIGRATE_ALL_HPP
#define MIGRATION_MIGRATE_ALL_HPP
#include "migration_policy_interface.hpp"
class MigrateAll : public MigrationPolicyInterface {
  public:
    MigrateAll(const std::vector<std::vector<double>> &population, const std::vector<double> &fitness_values)
        : MigrationPolicyInterface(population, fitness_values) {}
    virtual ~MigrateAll() = default;
    std::tuple<std::vector<std::vector<double>>, std::vector<double>> apply() override;
};
#endif