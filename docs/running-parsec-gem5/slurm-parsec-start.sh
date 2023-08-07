#!/bin/bash

#SBATCH --array=0-10000
#SBATCH --mem=9G
#SBATCH --output=/hpc/user/slurm-run-output/%A_%a.out

# Initialization
#################
. "/hpc/user/miniconda3/etc/profile.d/conda.sh"
conda activate gem5_env
# For the shared lib.so
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/hpc/user/miniconda3/envs/gem5_env/lib
#################

echo $SLURM_ARRAY_TASK_ID

python3 ./parsec-all-runner.py -n $SLURM_ARRAY_TASK_ID
