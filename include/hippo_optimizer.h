
#ifndef HIPPO_OPTIMIZER_H
#define HIPPO_OPTIMIZER_H

#include "function.h"
#include "hippo_math.h"
#include "hippo_random.h"
#include <algorithm>
#include <cstdint>
#include <iostream>
#include <random>

class hippo_optimizer {
  public:
    hippo_optimizer(uint32_t n_hippo, uint32_t max_iterations, double lowerbound, double upperbound,
                    uint32_t n_dimensions, const fun &fitness);
    void run();
    std::tuple<vector<double>, double> get_best_solution() const; 

  private:
    // initial parameters
    uint32_t n_hippo;
    uint32_t max_iterations;
    double lowerbound;
    double upperbound;
    uint32_t n_dimensions;
    double best_fitness = std::numeric_limits<double>::max();
    vector<double> best_solution;
    fun fitness;

    // data structures
    vector<double> fitness_vector;
    vector<double> lowerbound_vector; // solution's lowerbound
    vector<double> upperbound_vector; // solution's upperbound
    vvd population;                   // population of hippos

    void initialize();
    void explore(uint32_t best_idx, uint32_t iteration);
    void defend();
    void escape(uint32_t iteration);
};

#endif // HIPPO_OPTIMIZER_H