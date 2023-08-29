#!/bin/bash
#SBATCH --output=compilation.out
#SBATCH --cpus-per-task=9
#SBATCH --mem-per-cpu=1024

# conda initialize
. "/hpc/group/brownlab/fjm7/miniconda3/etc/profile.d/conda.sh"

conda activate gem5_env
# Needs help finding the shared libpython.so
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/hpc/group/brownlab/fjm7/miniconda3/envs/gem5_env/lib

# Run on 9 CPUs, specified by the -j flag. Settings set at the top
python `which scons` build/X86/gem5.fast PROTOCOL=MESI_Two_Level -j 9
# python3 `which scons` build/X86/gem5.opt PROTOCOL=MOESI_hammer -j 9
