# AGENTS.md

## Project overview

This repository is a C++23 optimization project. It implements the Hippo Optimizer (HO),
Grey Wolf Optimizer (GWO), and Whale Optimization Algorithm (WOA), benchmark objective
functions, and a parallel-island framework that combines optimizers through configurable
migration, selection, replacement, topology, and reconfiguration policies.

## Repository map

- `src/ho/`, `src/gwo/`, `src/woa/`: optimizer implementations.
- `src/core/`: common optimizer and problem interfaces and optimizer factory.
- `src/benchmark/`: benchmark functions and their factory.
- `src/parallel-islands/`: island execution and policy implementations.
- `src/linear_algebra/`, `src/random/`: vector operations and random number utilities.
- `apps/benchmark.cpp`, `apps/parallel_islands.cpp`: command-line applications.
- `test/`: existing tests.
- `scripts/`: experiment/result-generation utilities.
- `third_party/`: vendored dependencies; avoid modifying these for project changes.

For available CLI options, benchmark definitions, and usage examples, consult `readme.md`.

## Build and run

The project uses the root `Makefile` and `g++` with C++23. Build all applications with:

```sh
make
```

This creates executables in `bin/` and object files in `build/`. Remove build outputs with `make clean`.

Examples:

```sh
./bin/benchmark <optimizer_type> <function_type> <n_agents> <max_iterations>
./bin/parallel_islands --help
```

The benchmark optimizer IDs are documented in `readme.md`. Parallel-island options and their defaults are documented there as well.

## Change guidance

- Follow the existing C++ style in nearby files. The repository's `.clang-format` uses
  four-space indentation and a 110-column limit; use it when formatting C++ changes. The
  `.clang-tidy` file also have rules for enhanced readability that should be follow as
  well.
- Keep optimizer-specific behavior in the corresponding optimizer directory and shared
  interfaces in `src/core/`.
- Preserve the common `Optimizer` and `Problem` contracts when adding or changing
  optimizers or objective functions. Update the relevant factory and CLI wiring when
  introducing a new type.
- Keep island policies focused on their respective policy interfaces in
  `src/parallel-islands/`.
- Respect each benchmark's dimensionality and search bounds; they are defined in the
  benchmark implementation and summarized in `readme.md`.
- Avoid unrelated edits to vendored code under `third_party/`.
- Update `readme.md` when changing CLI flags, defaults, supported benchmark functions, or
  user-visible workflows.

## Validation

After C++ changes, run `make` to check compilation. The repository also has test sources under `test/`; inspect the relevant test and build setup before choosing how to run them, since the root `Makefile` does not define a test target.
