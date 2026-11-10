# Hippo Metaheuristic

## Cloning

```bash
git clone --recursive https://github.com/danielsaad.com/hippo-metaheuristic
```


## Compilation

To compile the source into its executables, do:

```bash
make
```

## Execution

### Parallel islands

Build the executables first:

```bash
make
```

Run the parallel-islands application with defaults:

```bash
./bin/parallel_islands
```

The default run uses Sphere (function 1), 30 agents per island, 100 generations, migration and
reconfiguration every 10 generations, one island for each optimizer, and 60 optimizer iterations
for each type. Since this runs an
optimization, it may take a while. Use `--help` to see the command-line options.

For example, to run Rastrigin with four GWO islands, two HO islands, and one WOA island:

```bash
./bin/parallel_islands --function 3 --agents 40 --generations 50 \
  --migration-rate 5 --reconfiguration-rate 15 --gwo 4 --ho 2 --woa 1 \
  --gwo-iterations 100 --ho-iterations 80 --woa-iterations 120
```

Each option is described below. Function and optimizer counts are numeric; policy values are
case-sensitive strings.

| Option | Default | Description |
|---|---:|---|
| `--function`, `-f` | `1` | Benchmark function number, from 1 to 14. See the function list below. |
| `--agents`, `-a` | `30` | Population size (number of candidate solutions) in each island. |
| `--generations`, `-g` | `100` | Number of parallel-island generations to run. |
| `--migration-rate` | `10` | Migration interval in generations. For example, `10` migrates at generations 10, 20, and so on. |
| `--reconfiguration-rate` | `10` | Reconfiguration interval in generations. Reconfiguration is attempted at each interval when the selected policy allows it. |
| `--gwo` | `1` | Number of islands initialized with Grey Wolf Optimizer (GWO). |
| `--ho` | `1` | Number of islands initialized with Hippo Optimizer (HO). |
| `--woa` | `1` | Number of islands initialized with Whale Optimization Algorithm (WOA). |
| `--gwo-iterations` | `60` | Maximum optimizer iterations for each GWO island. |
| `--ho-iterations` | `60` | Maximum optimizer iterations for each HO island. |
| `--woa-iterations` | `60` | Maximum optimizer iterations for each WOA island. |
| `--topology` | `graph` | Island connections: `graph` connects every island to every other island; `tree` connects islands in a binary-tree arrangement. |
| `--selection` | `bwr` | Migrant selection policy. `bwr` selects the best, worst, and one random candidate from the migration pool. |
| `--replacement` | `worst` | Island replacement policy. `worst` replaces the receiving island's worst candidates with migrants. |
| `--reconfiguration` | `stagnated` | Reconfiguration policy: `stagnated` changes an island's optimizer when it stagnates; `none` disables optimizer reconfiguration. |
| `--reconfiguration-choice` | `best` | Chooses the optimizer to use for reconfiguration. `best` takes it from the island with the best fitness. |

At least one optimizer island is required. `--agents`, `--generations`, and all three optimizer
iteration values must be positive. `--generations` controls how many times the island runner
advances the islands; each `--*-iterations` option sets the maximum-iteration value used to create
islands of that optimizer type.

### Benchmark functions

The `--function` number selects the objective function to minimize. Each function has a fixed
dimension and search bounds in the implementation; `--agents` changes population size, not the
function dimension.

| Number | Function | Dimensions and search bounds | Description |
|---:|---|---|---|
| 1 | Sphere | 30; each coordinate in `[-100, 100]` | Sum of squared coordinates. Smooth, convex, and minimized at the origin with value 0. |
| 2 | Rosenbrock | 5; each coordinate in `[-30, 30]` | A narrow curved valley formed by adjacent-coordinate terms. Its minimum is at `(1, 1, 1, 1, 1)`, with value 0. |
| 3 | Rastrigin | 30; each coordinate in `[-5.12, 5.12]` | A quadratic bowl with many cosine-generated local minima. The global minimum is at the origin with value 0. |
| 4 | Goldstein–Price | 2; each coordinate in `[-2, 2]` | A multimodal two-variable test function. Its global minimum is at `(0, -1)`, with value 3. |
| 5 | Schwefel | 30; each coordinate in `[-500, 500]` | A highly multimodal function with a broad search range. In this implementation it is the standard shifted form, whose global minimum is 0 near coordinates `420.9687`. |
| 6 | Schwefel 2.22 | 30; each coordinate in `[-100, 100]` | Combines the sum of absolute coordinate values and their product; this implementation rounds coordinates to the nearest integer before squaring and summing. Minimum: origin, value 0. |
| 7 | Eason | 2; each coordinate in `[-100, 100]` | A negative cosine product with an exponential well centered at `(π, π)`. Minimum: value `-1` at `(π, π)`. |
| 8 | Michalewicz | 10; each coordinate in `[0, π]` | A rugged multimodal function with sharp valleys; its formula uses exponent `m = 10`. The objective is negative, and the global minimum depends on dimension. |
| 9 | Hyper-Ellipsoid | 30; each coordinate in `[-5.12, 5.12]` | Weighted sum of squared coordinates, with larger weights on later coordinates. Minimum: origin, value 0. |
| 10 | Rotated Hyper-Ellipsoid | 30; each coordinate in `[-65.536, 65.536]` | Sum of cumulative squared-coordinate terms, creating coupled variables. Minimum: origin, value 0. |
| 11 | Ackley | 30; each coordinate in `[-32.768, 32.768]` | Combines an exponential distance term with a cosine term to create a nearly flat outer region and many local optima. Minimum: origin, value 0. |
| 12 | Griewank | 30; each coordinate in `[-600, 600]` | Combines a sum of squares with a product of cosine terms, producing many regularly spaced local minima. Minimum: origin, value 0. |
| 13 | Branin | 2; `x` in `[-5, 10]`, `y` in `[0, 15]` | A two-variable multimodal function with three global minima, each approximately `0.398`. |
| 14 | Six-Hump Camel | 2; `x` in `[-3, 3]`, `y` in `[-2, 2]` | A two-variable multimodal function with two global minima, each approximately `-1.032`. |

### Single-optimizer benchmark

The standalone benchmark application is also available:

```bash
./bin/benchmark <optimizer_type> <function_type> <n_agents> <max_iterations>
```

Optimizer types are `1` for HO, `2` for WOA, and `3` for GWO. Function types use the same
numbered list above.

## Experiments

The following functions were tested:
| Function                         | Optimal | Best Minima   | Solution                                                                                                                                                                                                                                                                                                                                                                                                               |
|----------------------------------|---------|---------------|------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Sphere Function                  |✅         | 0             | (0,0,0,0,0,0,-0,0,0,-0,0,0,0,0,0,0,0,0,0,0,0,0,0,-0,-0,-0,0,0,0,-0)                                                                                                                                                                                                                                                                                                                                                    |
| Rosenbrock Function              |✅         | 0.219         | (0.960851,0.901244,0.812426,0.66611,0.434319)                                                                                                                                                                                                                                                                                                                                                                          |
| Rastrigin Function               |✅         | 0             | (0,-0,-0,0,0,-0,0,0,-0,0,-0,0,-0,0,-0,-0,0,0,-0,-0,-0,0,0,-0,0,0,0,0,-0,0)                                                                                                                                                                                                                                                                                                                                             |
| Goldstein-Price Function         |✅         | 3             | (5.87454e-06,-1)                                                                                                                                                                                                                                                                                                                                                                                                       |
| Schwefel Function                |❌ (does not converge)         | -8.74622E+244 | (-2.81614e+228,-2.4708e+221,3.83191e+210,5.62555e+229,2.85279e+242,2.41675e+232,-2.62003e+230,-2.47156e+245,1.11419e+214,-4.78965e+228,2.39734e+218,1.24641e+242,2.78008e+210,-9.31727e+215,1.72572e+196,2.80313e+237,-1.66616e+224,-2.87912e+237,-1.39116e+235,-4.7085e+216,-3.58266e+231,-1.10607e+221,-1.43632e+218,5.04397e+216,-7.40358e+216,-3.7996e+221,-1.21677e+218,3.70466e+221,-1.02694e+232,-1.69978e+202) |
| Schwefel's Problem 2.22 Function |✅         | 0             | (0,0,0,-0,0,-0,0,0,0,0,0,0,-0,-0,0,0,0,0,0,-0,0,0,-0,0,0,0,0,0,0,0)                                                                                                                                                                                                                                                                                                                                                    |
| Eason's Function                 |✅         | -1            | (3.14188,3.1416)                                                                                                                                                                                                                                                                                                                                                                                                       |
| Michalewicz Function             |❌ (d=10)         | -6.47         | (2.03214,1.99323,1.28921,1.58296,1.7275,1.57643,2.51778,2.07823,0.739648,1.85955)                                                                                                                                                                                                                                                                                                                                      |
| Hyper-Ellipsoid Function         |✅         | 0             | (0,0,-0,0,0,-0,0,0,-0,0,-0,0,0,-0,0,0,0,0,0,0,-0,0,0,0,0,0,0,0,0,0)                                                                                                                                                                                                                                                                                                                                                    |
| Rotated Hyper-Ellipsoid Function |✅         | 0             | (0,0,-0,0,-0,0,0,0,0,-0,0,-0,0,0,0,0,-0,0,-0,0,0,0,0,-0,0,-0,-0,0,0,0)                                                                                                                                                                                                                                                                                                                                                 |
| Ackley Function                  |✅         | 0             | (0,0,0,0,0,0,-0,0,0,-0,0,0,-0,0,0,0,0,0,0,0,0,0,0,-0,0,0,0,0,-0,0)                                                                                                                                                                                                                                                                                                                                                     |
| Griewank Function                |✅         | 0             | (0,0,0,0,-0,-0,-0,0,-0,0,-0,0,-0,0,0,0,-0,-0,0,0,-0,-0,-0,0,-0,-0,0,-0,0,0)                                                                                                                                                                                                                                                                                                                                            |
| Branin Function                  |✅         | 0.398         | (9.42482,2.47501)                                                                                                                                                                                                                                                                                                                                                                                                      |
## Summary

Michalewicz: Works for `d=2` and `d=5`. For `d=10` it does not find the optimum solution.
Schwefel: does not converge.
