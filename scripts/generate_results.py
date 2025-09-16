import csv
import os
import subprocess
from pathlib import Path
script_dir = Path(__file__).resolve().parent
BENCHMARK_PATH = (script_dir / ".." / "bin" / "benchmark").resolve()

'''
Runs the optimizer over a function and returns
- The name of the function
- The best minima
- The solution of the minima
'''


def run_optimizer(f_choice: int) -> tuple[str, float, float]:
    cmd = [BENCHMARK_PATH, str(f_choice)]
    p = subprocess.run(cmd, text=True, capture_output=True)
    p.check_returncode()
    lines = p.stdout.splitlines()
    return lines[-3:]   # safe even if there are fewer than 3 lines


def main():
    results = []
    for f_choice in range(1, 14):
        print(f"Running optimizer for function {f_choice}")
        result = run_optimizer(f_choice)
        print(result)
        results.append(result)

    with open('results.csv', 'w') as f:
        writer = csv.writer(f)
        writer.writerow(['Function', 'Best Minima', 'Solution'])
        for result in results:
            writer.writerow([result[0], f'{float(result[1]):.3f}', result[2]])


if __name__ == "__main__":
    main()
