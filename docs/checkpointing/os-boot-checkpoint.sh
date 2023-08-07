#!/bin/bash

OUTPUT_DIR=/home/user/checkpoints/hack-back-4-core
NUM_THREADS=4

/home/user/gem5/build/X86/gem5-moesi_hammer.fast -d ${OUTPUT_DIR} /home/user/gem5/configs/example/fs.py --script=gem5/configs/boot/hack_back_ckpt.rcS --kernel=/home/user/ubuntu_images/kernel/vmlinux-5.4.49 --disk-image=/home/user/ubuntu_images/disk/x86-parsec --mem-size=3GiB -n ${NUM_THREADS} > ${OUTPUT_DIR}/output.txt
