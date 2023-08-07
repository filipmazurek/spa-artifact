#!/bin/bash

OUTPUT_DIR=/home/rapiduser/checkpoints/hack-back-4-core
NUM_CORES=4

/home/rapiduser/gem5/build/X86/gem5-moesi.fast -d ${OUTPUT_DIR} /home/rapiduser/gem5/configs/example/fs.py --script=${OUTPUT_DIR}/hack-back-ckpt.rcS --kernel=/home/rapiduser/ubuntu_images/kernel/vmlinux-5.4.49 --disk-image=/home/rapiduser/ubuntu_images/disk/x86-ubuntu-18_04-parsec --mem-size=3GiB -n ${NUM_CORES} > ${OUTPUT_DIR}/output.txt