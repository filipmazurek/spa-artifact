import argparse
import matplotlib.pyplot as plt

from smc.spa_frontend.spa import run_frontend

# Set confidence and proportion
confidence_level = 0.9
proportion = 0.5

# Use automatically-found granularity
granularity = None

# Set the default font size
plt.rcParams['font.size'] = 12
plt.subplots_adjust(top=0.85)

num_samples_used = 22


def round_to(val, precision=granularity):
    correction = precision if val >= 0 else precision
    return int(val / precision + correction) * precision


# Manually code in data
# This data was chosen to be a good visual example. It was taken from multiple random runs of SPA on the dataset
# data/csv/speedups/ferret-speedup-1MB-512kB.csv
data1 = [1.3985882772064133, 1.4233936273110466, 1.4815742975076331, 1.4513730499430773, 1.4765205323489523,
         1.404735345452333, 1.3856029805513528, 1.6010322464245896, 1.3629581579937944, 1.4463394851386622,
         1.4309264306508436, 1.519625575751497, 1.4537672052454924, 1.533575112149385, 1.4428399479564684,
         1.4724798501337737, 1.416218973630535, 1.6181425066956798, 1.3922943883414374, 1.6160742683245797,
         1.3678917739193994, 1.4063453143007765]
true_result = 1.4132421598769067

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
args.data_source = data1

# Run SPA
results = run_frontend(args)
spa_low, spa_high = (results[3], results[4])
# Extract the intermediate results from SPA
res_dict, conf_dict, lean_dict = results[5], results[6], results[7]
# Convert results to lists
speedup_list = list(res_dict.keys())
confidences_list = list(conf_dict.values())
leans_list = list(lean_dict.values())

# Update the confidences to be the confidence in the positive result
updated_conf_list = []
for conf, lean in zip(confidences_list, leans_list):
    if lean:
        updated_conf_list.append(conf)
    else:
        updated_conf_list.append(1 - conf)

# Set x-limits to be the min and max speedup
xmin = spa_low - 0.005
xmax = spa_high + 0.005

# Set y-limit from 0 to 1
plt.ylim(0, 1)
plt.xlim(xmin, xmax)

# Plot the desired confidence level
plt.axhline(y=confidence_level, color='k', linestyle='--')
plt.axhline(y=1 - confidence_level, color='k', linestyle='--')

# Plot all points to have a line
plt.plot(speedup_list, updated_conf_list, color='black', linestyle='dotted', marker='s', label='_nolegend_')

# Plot the leftmost certain point
plt.plot(speedup_list[0], updated_conf_list[0], color='green', marker='s', linestyle='')

# Plot the rightmost certain point
plt.plot(speedup_list[-1], updated_conf_list[-1], color='green', marker='s', linestyle='')

# Shade the area below 0.1 with a translucent green
plt.fill_between([xmin, xmax], [0, 0], 0.1, color='green', alpha=0.2, label='statistically significant')

# Shade the area above 0.9 with a translucent green
plt.fill_between([xmin, xmax], [0.9, 0.9], 1, color='green', alpha=0.2, label='_nolegend_')

plt.title(
    f'SPA Confidence Results for Ferret Speedup\n512kB vs 1MB L2 Cache\nN = {num_samples_used} | Proportion = {proportion} | Confidence = {confidence_level}')
plt.xlabel('Speedup')
plt.ylabel('Confidence in $positive$ Result')

rounded_speedup_list = [round(s, 2) for s in speedup_list]
plt.xticks(speedup_list, rounded_speedup_list)

# Add a legend
legend = plt.legend(loc='center right')
legend.set_bbox_to_anchor((1.0, 0.75))

plt.show()
