import argparse
import random
from scipy.stats import bootstrap, norm

from spa.smc_engine.data_generator import *
from spa.spa_frontend.spa import run_frontend
from spa.util.csv_reader import read_data

"""
ONLY to be used for proportion = 0.5. Includes rank testing and z-score. Use 22 samples only - these values are hardcoded.
"""

# Number of test points to check accuracy
trials = 100

# Set confidence and proportion
confidence_level = 0.9
proportion = 0.5

# Experimental files to analyze
csv_files = []

csv_files.append('../csv-results/ferret_3mb_l1miss1k.csv')
csv_files.append('../csv-results/ferret_3mb_runtime.csv')
csv_files.append('../csv-results/ferret_3mb_l2miss1k.csv')
csv_files.append('../csv-results/ferret_3mb_maxload.csv')
csv_files.append('../csv-results/ferret_3mb_tlbwritemiss1k.csv')

# Interval width comparison
spa_width_list = []
bootstrap_width_list = []
rank_width_list = []
analytical_width_list = []

# Use 22 samples for consistency
num_samples_used = 22

# Print the header
print(f'SPA vs bootstrap vs rank vs z-score:')
print(f'    Confidence level = {confidence_level}')
print(f'    Proportion = {proportion}')
print(f'    Number of samples used = {num_samples_used}')
print('\n')

# Set up SPA arguments
args = argparse.Namespace
args.property = ['ThresholdProperty']
args.data_source_2 = None
args.smc_only = False
args.granularity = None
args.proportion = float(proportion)
args.confidence = float(confidence_level)
args.search_start_point = None
args.iteration_limit = 50000
args.threshold = None
args.continuous = True


# Callable for bootstrap
def proportion_callable(data_list, axis):
    return np.quantile(data_list, 1 - proportion, axis)


# Repeat for every csv file
for csv_file in csv_files:
    # Set up all variables keeping track of accuracy
    num_spa_correct = 0
    num_bootstrap_correct = 0
    num_bootstrap_fail = 0
    num_rank_correct = 0
    num_analytical_correct = 0

    # Set up all lists keeping track of interval widths
    spa_width_list = []
    bootstrap_width_list = []
    rank_width_list = []
    analytical_width_list = []

    # Read in all csv data
    all_data = read_data(csv_file)
    all_data.sort()
    true_result = np.quantile(all_data, 1 - proportion)

    # For every trial, shuffle the data and run all CI methods
    for i in range(trials):
        random.shuffle(all_data)
        data = all_data[:num_samples_used]

        # Sort in-place for rank testing
        data.sort()

        # Create data sequence for bootstrap
        data_seq = (data,)

        # Run bootstrap. Note that this may throw an error in case of degenrate data
        bootstrap_result = bootstrap(data_seq, proportion_callable, confidence_level=confidence_level)
        bootstrap_low_high = (bootstrap_result.confidence_interval.low, bootstrap_result.confidence_interval.high)
        bootstrap_low, bootstrap_high = bootstrap_low_high

        # If bootstrapping can't complete, keep track of the failure and don't add the bootstrap width
        if np.isnan(bootstrap_low):
            num_bootstrap_fail += 1
        else:
            bootstrap_width_list.append(bootstrap_high - bootstrap_low)

        # Give a new data source argument to the argparser
        args.data_source = data

        # Run SPA
        results = run_frontend(args)
        spa_low, spa_high = (results[3], results[4])

        spa_width_list.append(spa_high - spa_low)

        # Rank testing
        # Manually set the index values for 22 samples and proportion=0.9
        lower_bound_index = 8
        upper_bound_index = 16

        rank_low = data[lower_bound_index]
        rank_high = data[upper_bound_index]

        rank_width_list.append(rank_high - rank_low)

        # Z-score CI
        analytical_low, analytical_high = norm.interval(confidence_level, loc=np.mean(data), scale=np.std(data))
        analytical_width_list.append(analytical_high - analytical_low)

        # Check accuracy of each confidence interval
        if spa_low <= true_result <= spa_high:
            num_spa_correct += 1
        if bootstrap_low <= true_result <= bootstrap_high:
            # Comparing to nan always results in false
            num_bootstrap_correct += 1
        if rank_low <= true_result <= rank_high:
            num_rank_correct += 1
        if analytical_low <= true_result <= analytical_high:
            num_analytical_correct += 1

    print(f'Data source = {csv_file}')
    print(f'  True value = {true_result}')
    print(f'  {trials} Trial Error Rates:')
    print(f'    SPA =       {round((trials - num_spa_correct) / trials, 2)}')
    print(f'    Bootstrap = {round((trials - num_bootstrap_correct) / trials, 2)}')
    print(f'    Rank =      {round((trials - num_rank_correct) / trials, 2)}')
    print(f'    Z-score =   {round((trials - num_analytical_correct) / trials, 2)}')
    print(f'  Normalized Interval Widths:')
    print(f'    SPA =       {np.mean(spa_width_list) / round(np.quantile(data, 1 - proportion), 2)}')
    print(f'    Bootstrap = {np.mean(bootstrap_width_list) / round(np.quantile(data, 1 - proportion), 2)}')
    print(f'    Rank =      {np.mean(rank_width_list) / round(np.quantile(data, 1 - proportion), 2)}')
    print(f'    Z-score =   {np.mean(analytical_width_list) / round(np.quantile(data, 1 - proportion), 2)}')
    print('  Other stats:')
    print(f'    Boostrap Failure Rate = {round(num_bootstrap_fail / trials, 2)}')
    print('\n')
