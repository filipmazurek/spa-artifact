#!/bin/bash

OUTPUT_DIR=/home/user/checkpoints/hack-back-quiesced-2-core

/home/user/gem5/build/X86/gem5-moesi.fast -d ${OUTPUT_DIR} /home/user/gem5/configs/example/fs.py --script=${OUTPUT_DIR}/hack-back-quiesced.rcS --kernel=/home/user/ubuntu_images/kernel/vmlinux-5.4.49 --disk-image=/home/user/ubuntu_images/disk/x86-parsec --mem-size=3GiB -n 2 > ${OUTPUT_DIR}/output.txt
