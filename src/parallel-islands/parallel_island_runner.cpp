#include "parallel-islands/parallel_island_runner.hpp"
#include "BS_thread_pool.hpp"
#include "rapidcsv.h"
#include <future>
#include <iostream>
#include <iterator>
#include <print>
#include <string>
#include <string_view>
#include <vector>

using std::println;

ParallelIslandRunner::ParallelIslandRunner(size_t n_threads, std::vector<HomogeneousIsland> islands,
                                           size_t n_generations, size_t migration_rate,
                                           size_t reconfiguration_rate)
    : n_threads_(n_threads), n_generations_(n_generations), migration_rate_(migration_rate),
      reconfiguration_rate_(reconfiguration_rate), islands_(std::move(islands)) {};

void
ParallelIslandRunner::run() {
    BS::thread_pool pool(n_threads_); // Create a thread pool with n_threads_ threads
    vector<std::future<void>> future(n_threads_);
    /**
     * Compute generations all islands with migrations between islands every
     * migration_rate_ generations and reconfiguration every reconfiguration_rate_
     * generations.
     */
    for (size_t gen = 0; gen <= n_generations_; gen++) { // for each generation
                                                         // Migrations

        std::print("Generation {} of {} with migration rate {} and reconfiguration rate {}\n", gen,
                   n_generations_, migration_rate_, reconfiguration_rate_);

        for (size_t i = 0; i < n_threads_; i++) {
            future[i] = pool.submit_task([this, i, gen] { islands_[i].run(gen == 0); });
        }

        for (size_t i = 0; i < n_threads_; i++) {
            future[i].wait();
        }

        // Snapshot the completed generation before reconfiguration changes optimizer type.
        for (size_t i = 0; i < n_threads_; i++) {
            auto optimizer_id = islands_[i].optimizer_->get_optimizer_id();
            auto [best_solution, best_fitness] = islands_[i].optimizer_->get_best_solution();
            if (best_fitness < islands_[i].best_fitness_) {
                islands_[i].best_solution_ = best_solution;
                islands_[i].best_fitness_ = best_fitness;
            }
            islands_[i].optimizer_->update_best_solution(islands_[i].best_solution_,
                                                         islands_[i].best_fitness_);
            islands_[i].convergence_curve_.push_back(islands_[i].best_fitness_);
            islands_[i].optimizer_history_.push_back(optimizer_id);
            std::println("Thread {} fitness {} optimizer {}", i, islands_[i].best_fitness_, optimizer_id);
        }

        bool migration_flag = gen > 0 and gen % migration_rate_ == 0;
        bool reconfiguration_flag = gen > 0 and gen % reconfiguration_rate_ == 0;

        if (reconfiguration_flag) {
            auto new_optimizer = manager_.choose_optimizer_for_reconfiguration(islands_);

            for (size_t i = 0; i < n_threads_; i++) {
                int old_type = islands_[i].optimizer_->get_optimizer_id();
                auto result = manager_.reconfigure_island(islands_[i], new_optimizer->clone());
                if (result) {
                    println("Island {} reconfigured from optimizer type {} with new optimizer type {}", i,
                            old_type, new_optimizer->get_optimizer_id());
                } else {
                    println("Island {} not reconfigured: type {}", i, old_type);
                }
            }
        }
        if (migration_flag) {
            // migrated_individuals[j] is the migration pool to the island j
            vector<vector<tuple<vector<vector<double>>, vector<double>>>> migration_individuals(n_threads_);

            // Extract individuals from each islands and build migration pool
            for (size_t i = 0; i < n_threads_; i++) {
                println("Extracting individuals from island {}", i);
                auto population_and_fitness = islands_[i].optimizer_->get_population_and_fitness();
                for (auto v : manager_.get_neighbors(i)) {
                    println("Puting individuals from {} into {} pool", i, v);
                    migration_individuals[v].push_back(population_and_fitness);
                }
            }

            // Select individuals from each island that will proceed to migration
            for (size_t i = 0; i < n_threads_; i++) {
                // println("Selecting individuals from island {}", j);
                vector<vector<double>> population_pool;
                vector<double> fitness_pool;
                for (auto &x : migration_individuals[i]) {
                    population_pool.insert(population_pool.end(), std::make_move_iterator(get<0>(x).begin()),
                                           std::make_move_iterator(get<0>(x).end()));
                    fitness_pool.insert(fitness_pool.end(), std::make_move_iterator(get<1>(x).begin()),
                                        std::make_move_iterator(get<1>(x).end()));
                }
                // Now filter the pool
                auto [p, f] = manager_.select_individuals(population_pool, fitness_pool);
                manager_.replace_individuals(islands_[i], p, f);
            }
        }
    }
}

void
ParallelIslandRunner::set_manager(ParallelIslandManager &&manager) {
    manager_ = std::move(manager);
}

void
ParallelIslandRunner::save_data() {
    rapidcsv::Document doc("", rapidcsv::LabelParams(0, -1));

    doc.SetColumnName(0, "gen");
    for (size_t i = 0; i < n_threads_; i++) {
        doc.SetColumnName(i * 2 + 1, "optimizer type");
        doc.SetColumnName(i * 2 + 2, "fitness");
    }

    for (size_t gen = 0; gen <= n_generations_; gen++) {
        std::vector<string> row;
        row.push_back(std::to_string(gen));
        for (size_t i = 0; i < n_threads_; i++) {
            row.push_back(std::to_string(islands_[i].optimizer_history_[gen]));
            std::ostringstream oss;
            oss << std::setprecision(std::numeric_limits<double>::max_digits10)
                << islands_[i].convergence_curve_[gen];
            std::string s = oss.str();
            row.push_back(s);
        }
        doc.SetRow(gen, row);
    }
    doc.Save("results.csv");
}
