#include "migration_migrate_all.hpp"

std::tuple<std::vector<std::vector<double>>, std::vector<double>>
MigrateAll::apply() {
    return std::make_tuple(population_, fitness_);
}
