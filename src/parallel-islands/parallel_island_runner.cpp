#include "parallel-islands/parallel_island_runner.hpp"
#include "BS_thread_pool.hpp"
#include <future>
#include <iostream>
#include <iterator>
#include <print>
#include <vector>

using std::print;
using std::println;

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
    }

    /**
     * Compute generations 1 to n_generations_ of all islands with migrations
     * between islands every migration_rate_ generations
     */
    for (size_t i = 0; i < n_generations_; i++) { // for each generation
                                                  // Migrations

        bool migration_flag = i % migration_rate_ == 0;
        // migrated_individuals[j] is the migration pool to the island j
        vector<vector<tuple<vector<vector<double>>, vector<double>>>> migration_individuals(n_threads_);
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
        }
    }
}