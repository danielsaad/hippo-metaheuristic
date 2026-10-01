#ifndef MIGRATION_MIGRATE_WORST_HPP
#define MIGRATION_MIGRATE_WORST_HPP
#include "migration_policy_interface.hpp"

class MigrateWorst : public MigrationPolicyInterface {
  public:
    MigrateWorst(const std::vector<std::vector<double>> &population,
                 const std::vector<double> &fitness_values)
        : MigrationPolicyInterface(population, fitness_values) {}

    virtual std::tuple<std::vector<std::vector<double>>, std::vector<double>>
    apply() override;

    void
    set_migrants_size(size_t n_migrants) {
        n_migrants_ = n_migrants;
    }

  private:
    size_t n_migrants_;
};
#endif