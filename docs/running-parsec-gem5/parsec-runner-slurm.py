import argparse
import os

num_samples = 200

# Cache inputs
l2_assoc = 16
l1d_size = '32kB'

l2_sizes = ['512kB', '1MB']

gem5_executable = '/hpc/user/gem5/build/X86/gem5-mesi.fast'
config_file = '/hpc/Ω/gem5/configs/example/fs.py'
checkpoint_storage = '/hpc/user/checkpoints/'

benchmarks = [ 'bodytrack', 'blackscholes', 'canneal', 'dedup', 'facesim', 'ferret', 'fluidanimate', 'freqmine', 'raytrace', 'streamcluster', 'swaptions']
input_sizes = ['simsmall', 'simmedium', 'simlarge']
num_cores_list = [2, 4]

results_dir_base = f'/hpc/user/new-data-collection'


def parse_args():
    parser = argparse.ArgumentParser()
    parser.add_argument('-n', '--sbatch', type=int,
                        help='Number of the sbatch runner. To be modulated to find which Run to do')
    args = parser.parse_args()
    return args


def find_run(goal_num):
    # Sanity check. Ensure that there are no more processes than we need
    max_runs = len(num_cores_list) * len(benchmarks) * len(input_sizes) * len(l2_sizes) * num_samples
    if goal_num > max_runs:
        print('The given sbatch number is greater than the total number of expected runs. Exiting.')
        exit()

    # A nice and understandable for loop to find which combination of benchmark, input, etc. to run.
    #   Maybe this should be redone with division and modulus?
    i = 0
    while True:
        for num_cores in num_cores_list:
            for benchmark in benchmarks:
                for input_size in input_sizes:
                    for l2_size in l2_sizes:
                        # Loop through individual samples first so that we get data as needed
                        for run_num in range(num_samples):
                            if i == goal_num:
                                return num_cores, benchmark, input_size, l2_size, run_num
                            else:
                                i += 1


args = parse_args()
sbatch_num = args.sbatch

num_cores, benchmark, input_size, l2_size, run_num = find_run(sbatch_num)

# Get the benchmark-specific checkpoint
checkpoint_dir = os.path.join(checkpoint_storage, 'cores_' + str(num_cores), benchmark, input_size)

# Get the output directory path
output_dir = os.path.join(results_dir_base, 'cores_' + str(num_cores), benchmark, input_size, 'l2_' + l2_size, 'run_' + str(run_num))

# If the output directory already exists, then skip this run
if os.path.exists(output_dir):
    # Get only the files in the directory
    files = [f for f in os.listdir(output_dir) if os.path.isfile(os.path.join(output_dir, f)) and f == 'stats.txt']
    if len(files) > 0:
        exit()

# Otherwise create the output directory
os.makedirs(output_dir)

# Create the command and the runscript it will use
# NOTE: Restoring from checkpoint=2. The first checkpoint is the one after OS boot.
#   Assuming that index starts at 1, and so 2 will restore the correct one
cmd_txt = f"{gem5_executable} -d {output_dir} {config_file} --checkpoint-dir={checkpoint_dir} --checkpoint-restore=2 --kernel=/hpc/user/ubuntu_images/kernel/vmlinux-5.4.49 --disk-image=/hpc/user/ubuntu_images/disk/x86-ubuntu-18_04-parsec --cpu-type=O3CPU -n {num_cores} --ruby --mem-size=3GiB --l2cache --num-l2caches=1 --l1d_size={l1d_size} --l1i_size=32kB --l2_size={l2_size} --l1d_assoc=8 --l2_assoc={l2_assoc} --param system.ruby.l2_cntrl0.l2_response_latency=16 --param system.ruby.l2_cntrl0.l2_request_latency=16 > {output_dir}/output.txt"

with open(os.path.join(output_dir, 'command.txt'), 'w') as f:
    f.write(cmd_txt)

print(cmd_txt)
os.system(cmd_txt)
