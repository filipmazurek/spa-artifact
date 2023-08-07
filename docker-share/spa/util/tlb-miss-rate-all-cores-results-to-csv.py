from pathlib import Path
import re

RESULTS_DIR = '../../smc-stats-txt/canneal-l2-512kB'

# TODO: Can parameterize whether to read simTicks or misses per kilo instructions
#   Remove the "no secondary" part
#   Add documentation

CSV_TITLE = 'canneal-512kb-tlb-miss-rate-4-core.csv'


def main():
    # key = 'simTicks'

    # For finding number of l2 cache misses per kilo instructions
    key_r = 'system.switch_cpus0.mmu.dtb.rdAccesses'
    key_w = 'system.switch_cpus0.mmu.dtb.wrAccesses'
    key_r_m = 'system.switch_cpus0.mmu.dtb.rdMisses'
    key_w_m = 'system.switch_cpus0.mmu.dtb.wrMisses'

    regex_r = f'(?<={key_r})\s+(\d+(?:\.\d+)?)'
    regex_w = f'(?<={key_w})\s+(\d+(?:\.\d+)?)'
    regex_r_m = f'(?<={key_r_m})\s+(\d+(?:\.\d+)?)'
    regex_w_m = f'(?<={key_w_m})\s+(\d+(?:\.\d+)?)'

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
                access_val = 0
                miss_val = 0
                for i in range(4):
                    key_r = f'system.switch_cpus{i}.mmu.dtb.rdAccesses'
                    key_w = f'system.switch_cpus{i}.mmu.dtb.wrAccesses'
                    key_r_m = f'system.switch_cpus{i}.mmu.dtb.rdMisses'
                    key_w_m = f'system.switch_cpus{i}.mmu.dtb.wrMisses'

                    regex_r = f'(?<={key_r})\s+(\d+(?:\.\d+)?)'
                    regex_w = f'(?<={key_w})\s+(\d+(?:\.\d+)?)'
                    regex_r_m = f'(?<={key_r_m})\s+(\d+(?:\.\d+)?)'
                    regex_w_m = f'(?<={key_w_m})\s+(\d+(?:\.\d+)?)'
                    val_r = re.search(regex_r, text_info)
                    val_w = re.search(regex_w, text_info)
                    val_r_m = re.search(regex_r_m, text_info)
                    val_w_m = re.search(regex_w_m, text_info)

                    val_r = int(val_r.group(0))
                    val_w = int(val_w.group(0))
                    val_r_m = int(val_r_m.group(0))
                    val_w_m = int(val_w_m.group(0))

                    access_val += val_r + val_w
                    miss_val += val_r_m + val_w_m

            except AttributeError:
                continue

            value = access_val / miss_val
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

