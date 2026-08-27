#include "parallel-islands/parallel_island_runner.hpp"
#include <iostream>
#include <print>
#include <thread>
#include <vector>

void ParallelIslandRunner::run() {
    std::vector<std::thread> threads;
    for (size_t i = 0; i < n_threads_; i++) {
        threads.emplace_back(static_cast<void (HomogeneousIsland::*)()>(&HomogeneousIsland::run),
                             &islands_[i]);
    }
    for (size_t i = 0; i < n_threads_; i++) {
        std::cout << "Joining thread " << i << std::endl;
        threads[i].join();
    }
    for (size_t i = 0; i < n_threads_; i++) {
        std::cout << "Thread " << i << " best solution: ";
        auto [best_solution, best_fitness] = islands_[i].optimizer_->get_best_solution();
        std::cout << "Best fitness: " << best_fitness << '\n';
    }
    // Migrations
    for (int i = 0; i < n_migrations_; i++) {
        vector<vector<std::vector<double>>> extracted_solutions(n_threads_);
        for (int j = 0; j < n_threads_; j++) {
            auto population_with_fitness = islands_[j].optimizer_->get_population_and_fitness();
            auto individuals = extract_individuals(population_with_fitness);
            extracted_solutions[j] = individuals;
        }

        for (size_t j = 0; j < n_threads_ / 2; j += 2) {
            std::print("Migrating solutions from island {} to island {} and vice-versa\n", j, j + 1);
            threads[j] = std::thread(&HomogeneousIsland::migrate_and_run, &islands_[j],
                                     std::vector<std::vector<double>>{extracted_solutions[j + 1]});
            threads[j + 1] = std::thread(&HomogeneousIsland::migrate_and_run, &islands_[j + 1],
                                         std::vector<std::vector<double>>{extracted_solutions[j]});
        }
        for (size_t j = n_threads_ / 2; j < n_threads_; j++) {
            std::print("Continuing evolution on island {}\n", j);
            threads[j] = std::thread(
                static_cast<void (HomogeneousIsland::*)(const std::vector<std::vector<double>> &)>(
                    &HomogeneousIsland::run),
                &islands_[j], extracted_solutions[j]);
        }
        for (size_t i = 0; i < n_threads_; i++) {
            std::cout << "Joining thread " << i << std::endl;
            threads[i].join();
        }
        for (size_t i = 0; i < n_threads_; i++) {
            std::cout << "Thread " << i << " best solution: ";
            auto [best_solution, best_fitness] = islands_[i].optimizer_->get_best_solution();
            std::cout << "Best fitness: " << best_fitness << "\n"; 
        }
    }
}