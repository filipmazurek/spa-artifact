import csv
from pathlib import Path
import re


# Only reading in the ferret benchmark run in Docker
benchmark_list = ['ferret']
benchsize_list = ['simsmall']
l2_cache_size_list = ['l2_1MB']
cores = '4'

# Has the setup to read in all relevant run combinations
for benchmark in benchmark_list:
    for benchsize in benchsize_list:
        for l2_cache_size in l2_cache_size_list:

            # Reading from RESULTS_DIR
            RESULTS_DIR = '../run-results/cores_4/ferret/simsmall/l2_1MB/'
            # Writing to CSV_TITLE
            CSV_TITLE = 'ferret-4_core-simsmall-l2_1MB' + '-misses_per_1k_inst.csv'

            # For finding number of l1 cache misses per kilo instructions (on the first core)
            key = 'system.ruby.l1_cntrl0.L1Dcache.m_demand_misses'
            key2 = 'simInsts'

            # Two regex, one for the number of misses, one for the number of instructions
            regex = f'(?<={key})\s+(\d+(?:\.\d+)?)'
            regex2 = f'(?<={key2})\s+(\d+(?:\.\d+)?)'

            results = []  # List of dictionaries, each dictionary has a value and a path
            result_vals =[]  # List of just the values
            baseline_vals = []

            # Rather than typing out the immediate baseline, read out the baseline value.
            print(RESULTS_DIR)

            for path in Path(RESULTS_DIR).rglob('stats.txt'):
                with open(path, 'r') as f:
                    try:
                        text_info = f.read()
                        value = re.search(regex, text_info)
                        num_inst_re = re.search(regex2, text_info)
                        # Get only the first value
                        value = int(value.group(0))
                        num_inst = int(num_inst_re.group(0))

                    except AttributeError:
                        # In case of gem5 not finishing the run in this directory
                        continue

                    # Divide by 1000 for kiloinstructions
                    value = value / (num_inst/1000)
                    results.append({'value': value, 'path': path})
                    result_vals.append(value)

            print(f'{len(result_vals)} values found!')

            # In case no values were found for this particular benchmark combination
            if len(result_vals) == 0:
                continue

            with open(CSV_TITLE, 'w') as file:
                writer = csv.writer(file, dialect='excel')
                writer.writerow(result_vals)
                print('finished writing')
