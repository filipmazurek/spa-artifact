# PARSEC Compilation Instructions

The following are instructions for how to compile PARSEC to be compatible with gem5. This means setting up the benchmark ROI so that they are the only parts recorded by gem5.


## Precompiled PARSEC Benchmarks

`spa-artifact/docker-share/parsec/` is the precompiled version of the PARSEC benchmarks with the gem5 hooks as described in the top-level README. To use gem5 using a disk image which contains these benchmarks:

1. Follow the `Downloads` instructions
2. Move the x86-parsec.img.gz to `ubuntu-images/`
```bash
gzip -d x86-parsec.img.gz
mv parsec.img x86-ubuntu-18_04-parsec
```
3. Mount the image and replace `/home/gem5/parsec-benchmark` with the precompiled copy
```bash
mkdir mnt
sudo mount -o loop,offset=1048576 x86-parsec mnt/
sudo rm -rf mnt/home/parsec-benchmark
sudo cp -r path-to/parsec-benchmark mnt/home/parsec-benchmark
sudo umount mnt/
```

That's all that's needed. Follow the below directions to recreate this precompiled PARSEC benchmark suite.


## Downloads

Download an x86 Ubuntu disk image with the PARSEC benchmark with ROI code for gem5 from [here](http://dist.gem5.org/dist/v22-1/images/x86/ubuntu-18-04/parsec.img.gz)

Or by the python script

```python
from gem5.resources.resource import Resource
disk_image=Resource(resource_name='x86-parsec')
```


## PARSEC Benchmark Setup

The Disk image in the above section has a precompiled version of the benchmarks with gem5 "hooks" that allow gem5 to call back to the Python script which started the simulator (See `gem5/configs/example/gem5_library/x86-parsec-benchmarks.py`).

This means that the PARSEC benchmarks themselves have had their `hook` code modified to use gem5 functions. We can't use the same code because we'll be using the `gem5/configs/example/fs.py` configuration script (as explained previously). Instead, we take advantage of the fact that all the heavy lifting has been done for use and instead replace the `exit` events with a `reset_stats` and `checkpoint` when beginning the ROI.

1. Create a VM / Docker container based on Ubuntu 18.04, to match the downloaded disk image (so the compiled PARSEC benchmarks can run on it).

To create a Docker image, use the included Dockerfile in this repository called `PARSEC-Dockerfile` (rename it to `Dockerfile`)

In the same directory as the Dockerfile, run the following command:
```bash
docker build -t parsec-builder .

docker run --name parsec-container --mount type=bind,source=/home/docker-share,destination=/shared-parsec -it parsec-builder bash
```

This will create a configuration that is the same as the Dockerfile, and start a Docker container that has a shared directory with the host and is interactive through the terminal with a bash interface.

In the shared interface, download the PARSEC benchmark. I use one that has been modified to work on newer Ubuntu versions. Practically all benchmarks compile on it. The following bash script should install everything needed. *Run it within the shared directory in the container.*

```bash
git clone https://github.com/cirosantilli/parsec-benchmark.git
cd parsec-benchmark
./configure
apt install texinfo
apt install autoconf
```

This should set up the build environment.

2. Copy the parsec-benchmark out of the disk image

More in-depth information about the following process can be found in the pdf `docs/arm-gem5-rsk.pdf`.

For this step, we want to remove the relevant hooks directory and place it in the parsec-benchmark downloaded earlier. There are no changes in the hooks. First, we need access to the disk image.

Go to the disk image directory and create a `mnt` folder.

```bash
mkdir mnt
```

Then find the size of the offset by running `fdisk -l` on the image

```bash
fdisk -l x86-parsec
```

Multipy the sector size (probably 512) by the `Boot Start` to get the offset size, and mount your image onto the empty directory.

```bash
sudo mount -o loop,offset=1048576 x86-parsec mnt/
```

The disk image will now be mounted on `mnt/`.

Copy the code from the `parsec-benchmark/pkgs/libs/hooks/src/` directory and replace the same folder in the downloaded `parsec-benchmark`. This will give us access to all m5 functions within the hooks code.

3. Modify the PARSEC hooks to reset gem5 stats and take checkpoints at ROI.

The heavy lifting was done for us. Go to `parsec-benchmark/pkgs/libs/hooks/src/hooks.c`. This is the code that will run at the ROI.

Under the function `void __parsec_roi_begin()`, replace the M5 code with the following code blocks. We modify the beginning of the ROI to take a checkpoint so that that checkpoint can be used to run only the ROI multiple times. Additionaly, at the end of ROI, we simply dump stats and continue. This is useful in case the benchmark has multiple ROI. As a result, stats are reset at the beginning of every ROI and then recorded at the end.

```C
#if ENABLE_M5_TRIGGER
// m5_work_begin(0,0);
printf(HOOKS_PREFIX" M5: taking a checkpoint \n");
fflush(NULL);
m5_checkpoint(0, 0);
m5_reset_stats(0, 0);
#endif
```

For `void __parsec_roi_end()`
```C
#if ENABLE_M5_TRIGGER
// m5_work_end(0,0);
m5_dump_stats(0, 0);
#endif
```

4. Recompile the PARSEC benchmark

In the `parsec-benchmark` directory

```bash
parsecmgmt -a uninstall -p parsec -c gcc-hooks
parsecmgmt -a clean -p parsec -c gcc-hooks
parsecmgmt -a uninstall -p parsec.hooks -c gcc-hooks
parsecmgmt -a clean -p parsec.hooks -c gcc-hooks
parsecmgmt -a build -p parsec -c gcc-hooks
```

Check the result of the build using

```bash
parsecmgmt -a status -p parsec
```

The last two benchmarks (`vips` and `x264`) in the PARSEC suite do not build correctly, but everything else should be fine.

5. Copy the PARSEC benchmark to the disk image

From the previously mounted image, we can now replace the pre-loaded `parsec-benchmark` with our own, recompiled copy.

```bash
sudo rm -rf mnt/home/parsec-benchmark
sudo cp -r path-to/parsec-benchmark mnt/home/parsec-benchmark
```

Now that the copying over is done, unmount the image
```bash
sudo umount mnt/
```


## Creating Checkpoints

All relevant checkpoint files are located in `docs/checkpointing/`.

1. Prerequisite: build both the `MOESI_Hammer` and `MESI_Two_Level` cache coherence protocols for gem5. Checkpoints may only be taken with `MOESI_Hammer` because this simple protocol writes back all modifications as cache entries are modified. `MESI_Two_Level` is the cache coherence protocol to use for the actual ROI runs because they will actually use both and L1 and L2 cache. Rename the gem5 executables for ease of use.

```bash
scons build/X86/gem5.fast -j 9 PROTOCOL=MESI_Two_Level
mv build/X86/gem5.fast build/X86/gem5-mesi.fast

scons build/X86/gem5.fast -j 9 PROTOCOL=MOESI_hammer
mv build/X86/gem5.fast build/X86/gem5-moesi_hammer.fast
```

2. Create checkpoints at the end of OS boot.
I used a beefy VM to create these checkpoints. Use the `hack-back` script (original found at `gem5/configs/boot/hack_back_ckpt.rcS`). The command to do so is saved in `os-boot-checkpoint.sh`. Here, it's possible to create a checkpoint using the fastest possible CPU model with no cache hierarchy for speedy checkpointing.

3. Create a checkpoint at the end of every permutation of input size and parsec benchmark. The code to do so is saved in `checkpoint-taker.py`. Simply run

```bash
python checkpoint-taker.py
```

After adding in the code to take checkpoints in the PARSEC hooks, this will create a checkpoint at the beginning of the ROI for every benchmark. This must be done so that there are checkpoints in the entrance to the ROI. Therefore the high volume of runs will only run the required sections and not waste runtime for common sections.


## Getting High Volume Runs

The reason for taking all those checkpoints is to have everything set up to get a ton of runs using detailed cores and memory on a computer cluster. The following instructions detail how to run these checkpointed files using SLURM.

The python script `parsec-runner-slurm.py` has all the basics to get the runs started. This script assumes that the structure of the checkoints is exactly the same as the ones taken earlier. This might require that you copy over the directory from where you took checkpoints to the computer cluster.

Modify the script so that all file paths are correct.

The script can be submitted using the slurm script `slurm-parsec-start.sh`. This script assumes that you are using the included conda environment to run. Please check all configurations and file paths and run it using

```bash
sbatch slurm-parsec-start.sh
```

This will begin running gem5 simulation for all parsec benchmarks.


## PARSEC Required Memory

To optimize the required memory per run for SLURM, use only the lowest amount of memory that each benchmark requires. This will allow the user to have more concurrent runs if the system is limited by memory. These values are based on gem5 running:

|                |              |
|----------------|--------------|
| protocol       | MOESI_hammer |
| cores          | 4 OoO        |
| memory system  | Ruby         |
| L2 size        | 3 MB         |
| PARSEC threads | 4            |


|               | Memory |
|---------------|--------|
| blackscholes  | 2 GB   |
| bodytrack     | 3 GB   |
| canneal       |        |
| dedup         | 9 GB   |
| facesim       |        |
| ferret        | 2 GB   |
| fluidanimate  | 2 GB   |
| freqmine      | 2 GB   |
| raytrace      |        |
| streamcluster | 2 GB   |
| swaptions     |        |
