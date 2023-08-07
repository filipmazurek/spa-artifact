"""Meta-runner: will kick off as many run-gem5-roi-docker.py executions as it can.
"""

from concurrent import futures
import os


num_available_cores = 4

# The total number of gem5 executions. To execute all benchmarks and paramter combinations, need
# len(num_cores_list) * len(benchmarks) * len(input_sizes) * len(l2_sizes) * num_samples

num_runs = 5


def runner(run_num):
    """Helper function to run a command in a subprocess"""
    os.system(f'python /shared/python-runners/run-gem5-roi-docker.py -n {run_num}')



# Running this on a 4 core machine. Limit to num_cpu workers at a time
with futures.ProcessPoolExecutor(max_workers=(num_available_cores-1)) as pool:
    pool.map(runner, list(range(num_runs)))
