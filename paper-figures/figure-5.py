import argparse
import matplotlib.pyplot as plt
import numpy as np
from scipy.stats import bootstrap, norm

from smc.spa_frontend.spa import run_frontend

# Set the default font size
plt.rcParams['font.size'] = 11.5

# Manually code in data
# This data was chosen to be a good visual example. It was taken from multiple random runs of SPA on the dataset
# data/csv/speedups/ferret-speedup-1MB-512kB.csv
data = [1.3985882772064133, 1.4233936273110466, 1.4815742975076331, 1.4513730499430773, 1.4765205323489523,
        1.404735345452333, 1.3856029805513528, 1.6010322464245896, 1.3629581579937944, 1.4463394851386622,
        1.4309264306508436, 1.519625575751497, 1.4537672052454924, 1.533575112149385, 1.4428399479564684,
        1.4724798501337737, 1.416218973630535, 1.6181425066956798, 1.3922943883414374, 1.6160742683245797,
        1.3678917739193994, 1.4063453143007765]

# True value
true_value = 1.4132421598769067

# Set confidence and proportion
proportion = 0.5
confidence_level = 0.9

# Use automatically-found granularity
granularity = None

# Feed into SPA all required arguments
args = argparse.Namespace
args.property = ['ThresholdProperty']
args.data_source_2 = None
args.smc_only = False
args.granularity = granularity
args.proportion = float(proportion)
args.confidence = float(confidence_level)
args.search_start_point = None
args.iteration_limit = 50000
args.threshold = None
args.continuous = True
# Give a new data source argument to the argparser
args.data_source = data

# Run SPA
results = run_frontend(args)
spa_low, spa_high = (results[3], results[4])

# Bootstrap
# Create data sequence for bootstrap
data_seq = (data,)


def proportion_callable(data_list, axis):
    return np.quantile(data_list, 1 - proportion, axis)


# Keep a static seed for reproducibility
seed = 42
rng = np.random.default_rng(seed)
# Run bootstrap
bootstrap_result = bootstrap(data_seq, proportion_callable, confidence_level=confidence_level, random_state=rng)
bootstrap_low, bootstrap_high = (bootstrap_result.confidence_interval.low, bootstrap_result.confidence_interval.high)

# Manually set the index values because otherwise it wants to use -inf and value 4.
lower_bound_index = 8
upper_bound_index = 16

# Sort the data in preparation for rank testing
data.sort()

# Determine ranks
rank_low = data[int(lower_bound_index)]
rank_high = data[int(upper_bound_index)]

# Calculate the confidence interval analytically
analytical_low, analytical_high = norm.interval(confidence_level, loc=np.mean(data), scale=np.std(data))

# Visualize the confidence intervals and true value
fig, ax = plt.subplots()
fig.subplots_adjust(top=0.855, left=0.135)

# Plot the confidence intervals with caps
cap_size = 5  # Cap size in points
ax.errorbar([(spa_low + spa_high) / 2], [3.5], xerr=[[(spa_high - spa_low) / 2]], fmt='', capsize=cap_size, label='SPA')
ax.errorbar([(bootstrap_low + bootstrap_high) / 2], [2.5], xerr=[[(bootstrap_high - bootstrap_low) / 2]], fmt='',
            capsize=cap_size, label='Bootstrap')
ax.errorbar([(rank_low + rank_high) / 2], [1.5], xerr=[[(rank_high - rank_low) / 2]], fmt='', capsize=cap_size,
            label='Rank')
ax.errorbar([(analytical_low + analytical_high) / 2], [0.5], xerr=[[(analytical_high - analytical_low) / 2]], fmt='',
            capsize=cap_size, label='Z-score')

# Plot the true value
ax.plot([true_value, true_value], [0, 4], 'k--', label='True value')

# Configure the plot
ax.set_xlim(analytical_low - .02, analytical_high + .02)
ax.set_ylim(0, 4)
ax.set_yticks([0.5, 1.5, 2.5, 3.5])
ax.set_yticklabels(['Z-score', 'Rank', 'Bootstrap', 'SPA'])
ax.set_xlabel('Speedup')
ax.set_title(
    f'SPA vs Bootstrap vs Rank vs Z-Score CI for Ferret Speedup\n512kB vs 1MB L2 Cache\nN = {len(data)} | Proportion = {proportion} | Confidence = {confidence_level}')
ax.legend()

# Show the plot
plt.show()
