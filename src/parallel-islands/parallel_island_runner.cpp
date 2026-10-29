#include "parallel-islands/parallel_island_runner.hpp"
#include "BS_thread_pool.hpp"
#include <future>
#include <iostream>
#include <iterator>
#include <print>
#include <vector>

using std::print;
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
     * Compute generation 0 of all islands
     */
    for (size_t i = 0; i < n_threads_; i++) {
        future[i] = pool.submit_task([this, i] { islands_[i].run(); });
    }
    for (size_t i = 0; i < n_threads_; i++) {
        std::cout << "Waiting thread " << i << std::endl;
        future[i].wait();
    }
    for (size_t i = 0; i < n_threads_; i++) {
        std::cout << "Thread " << i << " best solution: ";
        auto [best_solution, best_fitness] = islands_[i].optimizer_->get_best_solution();
        std::cout << "Best fitness: " << best_fitness << '\n';
        islands_[i].best_solution_ = best_solution;
        islands_[i].best_fitness_ = best_fitness;
        islands_[i].convergence_curve_.push_back(best_fitness);
    }

    /**
     * Compute generations 1 to n_generations_ of all islands with migrations
     * between islands every migration_rate_ generations
     */
    for (size_t i = 0; i < n_generations_; i++) { // for each generation
                                                  // Migrations

        std::print("Generation {} of {} with migration rate {} and reconfiguration rate {}\n", i,
                   n_generations_, migration_rate_, reconfiguration_rate_);

        bool migration_flag = i > 0 and i % migration_rate_ == 0;
        bool reconfiguration_flag = i > 0 and i % reconfiguration_rate_ == 0;

        // migrated_individuals[j] is the migration pool to the island j
        vector<vector<tuple<vector<vector<double>>, vector<double>>>> migration_individuals(n_threads_);
        if (reconfiguration_flag) {
            auto new_optimizer = manager_.choose_optimizer_for_reconfiguration(islands_);

            for (size_t j = 0; j < n_threads_; j++) {
                auto result = manager_.reconfigure_island(islands_[j], new_optimizer->clone());
                if (result) {
                    println("Island {} reconfigured with new optimizer", j);
                } else {
                    println("Island {} not reconfigured", j);
                }
            }
        }
        if (migration_flag) {

            // Extract individuals from each islands and build migration pool
            for (size_t j = 0; j < n_threads_; j++) {
                println("Extracting individuals from island {}", j);
                auto population_and_fitness = islands_[j].optimizer_->get_population_and_fitness();
                for (auto v : manager_.get_neighbors(j)) {
                    println("Puting individuals from {} into {} pool", j, v);
                    migration_individuals[v].push_back(population_and_fitness);
                }
            }

            // Select individuals from each island that will proceed to migration
            for (size_t j = 0; j < n_threads_; j++) {
                println("Selecting individuals from island {}", j);
                vector<vector<double>> population_pool;
                vector<double> fitness_pool;
                for (auto &x : migration_individuals[j]) {
                    population_pool.insert(population_pool.end(), std::make_move_iterator(get<0>(x).begin()),
                                           std::make_move_iterator(get<0>(x).end()));
                    fitness_pool.insert(fitness_pool.end(), std::make_move_iterator(get<1>(x).begin()),
                                        std::make_move_iterator(get<1>(x).end()));
                }
                // Now filter the pool
                auto [p, f] = manager_.select_individuals(population_pool, fitness_pool);
                manager_.replace_individuals(islands_[j], p, f);
            }
        }

        for (size_t i = 0; i < n_threads_; i++) {
            future[i] = pool.submit_task([this, i] { islands_[i].run(false); });
        }
        for (size_t i = 0; i < n_threads_; i++) {
            println("Waiting thread {}", i);
            future[i].wait();
        }

        for (size_t i = 0; i < n_threads_; i++) {
            std::cout << "Thread " << i << " best solution: ";
            auto [best_solution, best_fitness] = islands_[i].optimizer_->get_best_solution();
            std::cout << "Best fitness: " << best_fitness << "\n";
            islands_[i].best_solution_ = best_solution;
            islands_[i].best_fitness_ = best_fitness;
            islands_[i].convergence_curve_.push_back(best_fitness);
        }
    }
}

void
ParallelIslandRunner::set_manager(ParallelIslandManager &&manager) {
    manager_ = std::move(manager);
}
