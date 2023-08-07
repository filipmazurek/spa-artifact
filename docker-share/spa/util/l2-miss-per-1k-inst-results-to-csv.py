from pathlib import Path
import re

RESULTS_DIR = '../../smc-stats-txt/ferret-l2-512kB'

# TODO: Can parameterize whether to read simTicks or misses per kilo instructions
#   Remove the "no secondary" part
#   Add documentation

CSV_TITLE = 'ferret-512kb-l2-miss-rate-1k-inst.csv'


def main():
    # key = 'simTicks'

    # For finding number of l2 cache misses per kilo instructions
    key_r = 'simInsts'
    key_r_m = 'system.ruby.l2_cntrl0.L2cache.m_demand_misses'

    regex_r = f'(?<={key_r})\s+(\d+(?:\.\d+)?)'
    regex_r_m = f'(?<={key_r_m})\s+(\d+(?:\.\d+)?)'

    results = []
    result_vals = []

    # Rather than typing out the immediate baseline, read out the baseline value.
    print(RESULTS_DIR)

    for path in Path(RESULTS_DIR).rglob('stats.txt'):
        with open(path, 'r') as f:
            if path.match('*/no_second/*/*'):
                continue
            try:
                text_info = f.read()
                val_r = re.search(regex_r, text_info)
                val_r_m = re.search(regex_r_m, text_info)

                val_r = int(val_r.group(0))
                val_r_m = int(val_r_m.group(0))

            except AttributeError:
                continue

            value = (val_r_m) / (val_r / 1000)
            results.append({'value': value, 'path': path})
            result_vals.append(value)

    print(f'{len(result_vals)} values found!')

    print('writing to CSV File')
    import csv
    with open(CSV_TITLE, 'w') as file:
        writer = csv.writer(file, dialect='excel')
        writer.writerow(result_vals)
        print('finished writing')


if __name__ == '__main__':
    main()

