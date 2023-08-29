#!/bin/bash

cd /shared/ubuntu-images/disk/
mkdir mnt/
sudo mount -o loop,offset=1048576 x86-ubuntu-18_04-parsec mnt/
rm -rf mnt/home/gem5/parsec-benchmark/pkgs/apps/ferret
cp -r /shared/precompiled-ferret/ /shared/ubuntu-images/disk/mnt/home/gem5/parsec-benchmark/pkgs/apps/ferret/

sudo umount mnt
