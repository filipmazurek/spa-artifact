#!/bin/bash
#SBATCH --output=parsec-example-script.out

# conda initialize
. "/hpc/group/brownlab/fjm7/miniconda3/etc/profile.d/conda.sh"

conda activate gem5_env
# Needs help finding the shared libpython.so
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/hpc/group/brownlab/fjm7/miniconda3/envs/gem5_env/lib

# Run gem5 with the parsec script
build/X86/gem5.opt configs/example/gem5_library/x86-parsec-benchmarks.py  --benchmark  ferret --size simsmall
