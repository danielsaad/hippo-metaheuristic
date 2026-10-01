#include "migration_migrate_none.hpp"

std::tuple<std::vector<std::vector<double>>, std::vector<double>>
MigrateNone::apply() {
    return std::make_tuple(std::vector<std::vector<double>>(), std::vector<double>());
}