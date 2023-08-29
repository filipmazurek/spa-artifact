#!/bin/bash

bash Miniconda3-py38_23.5.2-0-Linux-x86_64.sh

eval "$(/root/miniconda3/bin/conda shell.bash hook)"

# Create the SPA environment
conda env create -f environment.yml
