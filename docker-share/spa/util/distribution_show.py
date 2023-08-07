import matplotlib.pyplot as plt
import numpy as np
import scipy.stats as st
import os

from smc.util.csv_reader import read_data

"""
Plots histogram of given data
"""

result_dir = '/Users/filipmazurek/Documents/smc/csv-results/micro_data_collection'

benchmarks = ['blackscholes', 'bodytrack', 'canneal', 'dedup']
input_sizes = ['simsmall', 'simmedium']
cores = ['cores_2', 'cores_4']
l2_cache_sizes = ['l2_512kB', 'l2_1MB']
metrics = ['runtime', 'misses_per_1k_inst']

files = []
# for benchmark in benchmarks:
#     for input_size in input_sizes:
#         for core in cores:
#             for l2_cache_size in l2_cache_sizes:
#                 for metric in metrics:
#                     files.append(f'{result_dir}/{benchmark}-{input_size}-{core}-{l2_cache_size}-{metric}.csv')

files = ['/Users/filipmazurek/Documents/smc/csv-results/legacy/parsec/ferret-small-l2_1mb-simticks-3_thread-2_core.csv', '/Users/filipmazurek/Documents/smc/csv-results/legacy/parsec/ferret-small-l2_1mb-simticks-4_thread-4_core.csv', '/Users/filipmazurek/Documents/smc/csv-results/legacy/parsec/ferret-small-l2_8mb-simticks-3_thread-2_core.csv', '/Users/filipmazurek/Documents/smc/csv-results/legacy/parsec/ferret-small-l2_8mb-simticks-4_thread-4_core.csv']

def create_distribution(filename: str):
    num_bins = 10

    # Get the string of the csv file
    name = filename.split('/')[-1].split('.')[0]
    values = read_data(filename)

    # Create histogram
    plt.hist(values, bins=num_bins)

    # For all necessary labels on plot
    plt.ylabel('Frequency')
    plt.xlabel('Data')
    plt.title(f'{name} Distribution')

    # plt.axvline(x=np.mean(values), color = 'k', linestyle='--')

    # plt.savefig(f'../plots/distributions/{name}.png')
    # plt.ylim((0, 20))
    # plt.xlim((0, 1000))
    plt.show()
    plt.clf()


if __name__ == '__main__':
    for file in files:
        try:
            create_distribution(file)
        except:
            continue
