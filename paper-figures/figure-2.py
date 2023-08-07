import matplotlib.pyplot as plt
import numpy as np

import smc.util.csv_reader as csv_reader

# Extract the data from the CSV file
data_points = csv_reader.read_data('../csv-results/paper/ferret_3mb_runtime.csv')

# Calculate the 50th and 90th percentiles
p90 = np.percentile(data_points, 90)
p50 = np.percentile(data_points, 50)

# Set the default font size
plt.rcParams['font.size'] = 12

# Create the histogram
fig, ax = plt.subplots()
n, bins, patches = ax.hist(data_points, bins=20, color='skyblue')

# Add vertical lines for the percentiles
ax.axvline(p50, color='black', linestyle='--', label='F = 0.5')
ax.axvline(p90, color='brown', linestyle='--', label='F = 0.9')

# Set the axis labels, title, and legend
ax.set_xlabel('Runtime (s)')
ax.set_ylabel('Frequency')
ax.set_title('Ferret Runtime on Simulated Machine')
ax.legend()

plt.show()
