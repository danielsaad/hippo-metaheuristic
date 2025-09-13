# Hippo Metaheuristic

## Compilation

To compile the source into its executables, do:

```bash
make
```

## Execution

You can run this metaheuristic with several benchmark functions by issuing the command.

```bash
./bin/benchmark
```

## Experiments

The following functions were tested:

## Summary

Michalewicz: Works for `d=2` and `d=5`. For `d=10` it does not find the optimum solution.
Hyper-Ellipsoid: Works for `d=30`.
Rotated Hyper-Ellipsoid: Works for `d=30`.
Ackley: Works for `d=30` within `10^{-16}` of optimum.
Griewank: Works for `d=30`.
Branin: Works for `d=2`.