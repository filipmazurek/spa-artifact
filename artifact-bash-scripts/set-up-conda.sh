#!/bin/bash

bash Miniconda3-py38_23.5.2-0-Linux-x86_64.sh

# Immediately activate the base environment
conda activate

# Create the SPA environment and activate it
conda env create -f environment.yml
conda activate spa
