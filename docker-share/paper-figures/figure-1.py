import matplotlib.pyplot as plt
import numpy as np

import spa.util.csv_reader as csv_reader

# Extract the data from the CSV file
data_points = csv_reader.read_data('../csv-results/real-machine/real-runtime-ferret.csv')

# Calculate the 50th, 80th, and 90th percentiles
p90 = np.percentile(data_points, 90)
p80 = np.percentile(data_points, 80)
p50 = np.percentile(data_points, 50)

# Set the default font size
plt.rcParams['font.size'] = 12

# Create the histogram
fig, ax = plt.subplots()
n, bins, patches = ax.hist(data_points, bins=20, color='skyblue')

# Add vertical lines for the percentiles
ax.axvline(p50, color='black', linestyle='--', label='F = 0.5')
ax.axvline(p80, color='green', linestyle='--', label='F = 0.8')
ax.axvline(p90, color='brown', linestyle='--', label='F = 0.9')

# Set the axis labels, title, and legend
ax.set_xlabel('Runtime (s)')
ax.set_ylabel('Frequency')

ax.set_title('Ferret Runtime on Real Machine')
ax.legend()

plt.savefig('paper-figure-1.png')
