#! /bin/bash

# This script is to build gem5 on Ubuntu 20.04

# Required packages for gem5
sudo apt install build-essential git m4 scons zlib1g zlib1g-dev libprotobuf-dev protobuf-compiler libprotoc-dev libgoogle-perftools-dev python3-dev python-is-python3 libboost-all-dev pkg-config

# Download gem5
git clone https://gem5.googlesource.com/public/gem5

cd gem5

# Get the correct tag
git checkout v22.1.0

git branch -b v22.1.0

# Build the MOESI_hammer version for checkpointing
python3 'which scons' build/X86/gem5.fast -j 4 PROTOCOL="MOESI_hammer"

# For running experiments, build the MESI_two_level instead
# python3 'which scons' build/X86/gem5.fast -j 4 PROTOCOL="MOESI_hammer"
