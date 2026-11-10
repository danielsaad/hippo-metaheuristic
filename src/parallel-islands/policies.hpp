#ifndef POLICIES_HPP
#define POLICIES_HPP

// Choice of reconfiguration
#include "reconfiguration_choice_best.hpp"
#include "reconfiguration_choice_policy.hpp"

// Reconfiguration of the islands
#include "reconfiguration_policy_interface.hpp"
#include "reconfiguration_reconfigure_stagnated.hpp"
#include "reconfiguration_reconfigure_none.hpp"

// Replacement of individuals in the island
#include "replace_policy_interface.hpp"
#include "replace_worst.hpp"

// Selection of individuals to migrate
#include "selection_bwr.hpp"
#include "selection_policy_interface.hpp"

// Topology
#include "topology_complete_graph.hpp"
#include "topology_complete_tree.hpp"
#include "topology_policy_interface.hpp"

#endif