import argparse
import matplotlib.pyplot as plt
import numpy as np
import os
import random
from scipy.stats import bootstrap, norm

from spa.util.csv_reader import read_data
from spa.spa_frontend.spa import run_frontend

# Read in all data
csv_file = "../csv-results/ferret_3mb_tlbwritemiss1k.csv"
all_data = read_data(csv_file)

# Number of seeds to average over
num_seeds = 10
os.urandom(50)

# Set proportion
prop = 0.5

# Use 22 samples for consistency
num_data_points = 22


# Callable for bootstrap
def proportion_callable(data_list, axis):
    return np.quantile(data_list, 1 - prop, axis)


# Prep the plot axes
totalYAxis = []
totalXAxis = []

# Set up the confidence points
confidence_points = []
for x in range(90, 100):
    confidence_points.append(x / 100)
confidence_points.append(0.999)

# Repeat for every seed average
for x in range(num_seeds):
    tempTotalYAxis = []
    random.shuffle(all_data)

    # Repeat for every confidence level
    for confidence_level in confidence_points:
        yAxis = []
        xAxis = []
        data1 = all_data[:num_data_points]

        xAxis.append(num_data_points)

        # Set up SPA arguments
        args = argparse.Namespace
        args.property = ['ThresholdProperty']
        args.data_source = data1
        args.data_source_2 = None
        args.smc_only = False
        args.granularity = None
        args.proportion = float(prop)
        args.confidence = float(confidence_level)
        args.search_start_point = None
        args.iteration_limit = 10000
        args.threshold = None
        args.continuous = True
        # Run SPA
        results = run_frontend(args)
        spa_low, spa_high = (results[3], results[4])

        # If SPA fails, note
        if spa_low == None or spa_high == None:
            yAxis.append(-1)
        else:
            # Append the SPA confidence interval width
            yAxis.append(spa_high - spa_low)

        # Create a sequence for bootstrap
        data1_seq = (data1,)

        # Run bootstrap
        bootstrap_result = bootstrap(data1_seq, proportion_callable, confidence_level=confidence_level)
        bootstrap_low_high = (bootstrap_result.confidence_interval.low, bootstrap_result.confidence_interval.high)
        bootstrap_low, bootstrap_high = bootstrap_low_high

        # Sort data for rank testing
        data1.sort()

        # Calculate the confidence interval bounds for rank testing
        quantile = 1 - prop
        # Find the z-critical value
        z_critical = norm.ppf(1 - (1 - confidence_level) / 2)  # 95% CI, two-tailed test (1-0.95)/2 = 0.025, so 0.975
        # Calculate the upper and lower bound
        num_samples = len(data1)
        # Subtract 1 to account for 0-indexing
        lower_bound_index = np.floor(
            num_samples * quantile - (z_critical * np.sqrt(num_samples * quantile * (1 - quantile))) - 1)
        upper_bound_index = np.ceil(
            num_samples * quantile + (z_critical * np.sqrt(num_samples * quantile * (1 - quantile))) - 1)

        # Adjust the bounds if they exceed the data
        if lower_bound_index < 0:
            lower_bound_index = 0
        if upper_bound_index > num_samples:
            upper_bound_index = num_samples - 1

        # Get the rank testing CI bounds
        rank_low = data1[int(lower_bound_index)]
        rank_high = data1[int(upper_bound_index)]

        # Calculate the confidence interval analytically
        analytical_low, analytical_high = norm.interval(confidence_level, loc=np.mean(data1), scale=np.std(data1))

        # Append the confidence interval widths
        if bootstrap_low == None or bootstrap_high == None:
            yAxis.append(-1)
        else:
            yAxis.append(bootstrap_high - bootstrap_low)
        if rank_low == None or rank_high == None:
            yAxis.append(-1)
        else:
            yAxis.append(rank_high - rank_low)
        if analytical_high == None or analytical_low == None:
            yAxis.append(-1)
        else:
            yAxis.append(analytical_high - analytical_low)

        tempTotalYAxis.append(yAxis)
    totalYAxis.append(tempTotalYAxis)

totalXAxis = confidence_points
dataY = [[], [], [], []]
dataX = [[], [], [], []]

# Average over all seeds
for y in range(0, len(totalYAxis[0])):
    temp = [[], [], [], []]
    for z in range(0, len(totalYAxis[0][y])):
        for x in range(0, num_seeds):
            temp[z].append(totalYAxis[x][y][z])
    np.mean(temp[0]) / round(np.quantile(all_data, 1 - prop), 2)
    dataY[0].append(np.mean(temp[0]) / round(np.quantile(all_data, 1 - prop), 2))
    dataY[1].append(np.mean(temp[1]) / round(np.quantile(all_data, 1 - prop), 2))
    dataY[2].append(np.mean(temp[2]) / round(np.quantile(all_data, 1 - prop), 2))
    dataY[3].append(np.mean(temp[3]) / round(np.quantile(all_data, 1 - prop), 2))

finalDataY = [[], [], [], []]
for x in range(0, 4):
    for y in range(0, len(dataY[x])):
        if dataY[x][y] > 0:
            finalDataY[x].append(dataY[x][y])
            dataX[x].append(totalXAxis[y])

# Write to CSV
plt.figure(figsize=(10, 7))

plt.plot(dataX[0], finalDataY[0], label="SPA")
plt.plot(dataX[1], finalDataY[1], label="Bootstrapping")
plt.plot(dataX[2], finalDataY[2], label="Rank")
plt.plot(dataX[3], finalDataY[3], label="Z-score")

plt.xlabel('Confidence', fontsize=18)
plt.ylabel('Normalized Confidence Interval Width', fontsize=18)
plt.title(
    f'Effects of Confidence on Interval Width\nPARSEC Ferret Benchmark TLB Write Misses/1K Instructions\n'
    f'Averaged over {num_seeds} random seeds | N=22 | Proportion=0.5',
    fontsize=18)
plt.xticks([0.9, 0.92, 0.94, 0.96, 0.98, 0.999], fontsize=16)
plt.yticks(fontsize=16)
plt.xlim([0.898, 1.002])

plt.legend(fontsize=16)
plt.savefig('paper-figure-12.png', bbox_inches='tight')
