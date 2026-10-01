#ifndef MIGRATION_MIGRATE_RANDOM_HPP
#define MIGRATION_MIGRATE_RANDOM_HPP
#include "migration_policy_interface.hpp"

class MigrateRandom : public MigrationPolicyInterface {
  public:
    MigrateRandom(const std::vector<std::vector<double>> &population,
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