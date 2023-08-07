from concurrent import futures
import os


gem5_executable = '/home/user/gem5/build/X86/gem5-moesi.fast'
config_file = '/home/user/gem5/configs/example/fs.py'
checkpoint_src = '/home/user/checkpoints'

checkpoint_dest = '/home/user/checkpoints'

kernel_path = '/home/user/ubuntu_images/kernel/vmlinux-5.4.49'
disk_image_path = '/home/user/ubuntu_images/disk/x86-ubuntu-18_04-parsec'
static_options = ' --mem-size=3GiB '

benchmarks = ['blackscholes', 'bodytrack', 'canneal', 'dedup', 'facesim', 'ferret', 'fluidanimate', 'freqmine', 'raytrace', 'streamcluster', 'swaptions']
input_sizes = ['simsmall', 'simmedium'] #, 'simlarge']  # exclude simlarge for now

num_cores_list = [2, 4]


def runner(command):
    """Helper function to run a command in a subprocess"""
    os.system(command)


def main():

    arguments = []
    for num_cores in num_cores_list:
        for benchmark in benchmarks:
            for input_size in input_sizes:
                # Get output directory
                output_dir = os.path.join(checkpoint_dest, 'cores_' + str(num_cores), benchmark, input_size)

                # Skip already created checkpoints
                if os.path.exists(output_dir):
                    # Get only the checkpoint directories in the directory
                    cpt_dirs = [d for d in os.listdir(output_dir) if os.path.isdir(os.path.join(output_dir, d)) and d.startswith('cpt')]

                    # If there are 2 cpt dirs, skip this argument
                    if len(cpt_dirs) >= 2:
                        continue

                # Create the output directory if it doesn't exist
                if not os.path.exists(output_dir):
                    os.makedirs(output_dir)

                # Create the path of where the runscript will be
                runscript_file = os.path.join(output_dir, 'runscript.rcS')

                # Find the checkpoint dir
                checkpoint_dir = os.path.join(checkpoint_src, 'hack-back-quiesced-' + str(num_cores) + '-core')

                # Create the command and the runscript it will use
                # Note: checkpoint dir will be the own dir - if new checkpoints are dropped, they'll be put in the checkpoint dir
                cmd_txt = f"{gem5_executable} -d {output_dir} {config_file} --checkpoint-dir={output_dir} --checkpoint-restore=1 --script={runscript_file} --kernel={kernel_path} --disk-image={disk_image_path} --num-cpus={num_cores} {static_options}  > {output_dir}/output.txt"
                runscript_txt = f'#!/bin/bash\ncd /home/gem5/parsec-benchmark\nsource ./env.sh\nparsecmgmt -a run -p {benchmark} -c gcc-hooks -i {input_size} -n {num_cores}'

                # Write out the runscript and command
                with open(runscript_file, 'w') as f:
                    f.write(runscript_txt)

                with open(os.path.join(output_dir, 'command.sh'), 'w') as f:
                    f.write(cmd_txt)

# TODO: put in your correct checkpoint files!!

                # Copy over the checkpoint to the new directory
                if num_cores == 2:
                    os.system(f'cp -r {checkpoint_dir}/cpt.4056004998500 {output_dir}/cpt.4056004998500')
                elif num_cores == 4:
                    os.system(f'cp -r {checkpoint_dir}/cpt.3754074832500 {output_dir}/cpt.3754074832500')

                arguments.append(cmd_txt)


    # Running this on a 4 core machine. Limit to 3 workers at a time
    with futures.ProcessPoolExecutor(max_workers=3) as pool:
        pool.map(runner, arguments)

if __name__ == '__main__':
    main()
