import os
from pathlib import Path
import re


benchmark_list = ['blackscholes',  'bodytrack',  'canneal',  'dedup',  'ferret', 'fluidanimate',  'freqmine',  'streamcluster', 'swaptions', 'canneal',  'facesim',  'ferret',  'fluidanimate',  'swaptions', 'fluidanimate', 'freqmine', 'streamcluster']
benchsize_list = ['simsmall']
l2_cache_size_list = ['l2_1MB']

user = 'my-user'
cores = 'cores_4'

def main():
    for benchmark in benchmark_list:
        for benchsize in benchsize_list:
            for l2_cache_size in l2_cache_size_list:


                RESULTS_DIR = os.path.join('/cluster', user, 'new-data-collection', cores, benchmark, benchsize, l2_cache_size)

                CSV_TITLE = '-'.join([benchmark, benchsize, cores, l2_cache_size]) + '-simTicks.csv'

                key = 'simTicks'

                # For finding number of l2 cache misses per kilo instructions
                # key = 'system.ruby.l2_cntrl0.L2cache.m_demand_misses'
                # key2 = 'simInsts'

                regex = f'(?<={key})\s+(\d+(?:\.\d+)?)'
                # regex2 = f'(?<={key2})\s+(\d+(?:\.\d+)?)'

                results = []
                result_vals =[]
                baseline_vals = []

                # Rather than typing out the immediate baseline, read out the baseline value.
                print(RESULTS_DIR)

                for path in Path(RESULTS_DIR).rglob('stats.txt'):
                    with open(path, 'r') as f:
                        if path.match('*/no_second/*/*'):
                            try:
                                value = re.search(regex, f.read())
                                value = int(value.group(0))
                                baseline_vals.append(value)
                                # print(path)
                                # print(value)
                            except AttributeError:
                                continue
                        else:
                            try:
                                text_info = f.read()
                                value = re.search(regex, text_info)
                                # num_inst_re = re.search(regex2, text_info)
                                value = int(value.group(0))
                                # num_inst = int(num_inst_re.group(0))

                            except AttributeError:
                                continue

                            # value = value / (num_inst/1000)
                            results.append({'value': value, 'path': path})
                            result_vals.append(value)


                print(f'{len(result_vals)} values found!')

                if len(result_vals) == 0:
                    continue

                print('writing to CSV File')
                import csv
                with open(CSV_TITLE, 'w') as file:
                    writer = csv.writer(file, dialect='excel')
                    writer.writerow(result_vals)
                    print('finished writing')


if __name__ == '__main__':
    main()
