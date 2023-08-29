#!/bin/bash

mkdir /shared/ubuntu-images
mkdir /shared/ubuntu-images/kernel/
mkdir /shared/ubuntu-images/disk/

cd /shared/ubuntu-images/kernel/
wget http://dist.gem5.org/dist/v22-1/kernels/x86/static/vmlinux-5.4.49

cd /shared/ubuntu-images/disk/
wget http://dist.gem5.org/dist/v22-1/images/x86/ubuntu-18-04/parsec.img.gz

gzip -d parsec.img.gz
mv parsec.img x86-ubuntu-18_04-parsec
