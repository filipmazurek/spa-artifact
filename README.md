# SPA Artifact

This repository consists of all required code, data, and instructions required to replicate the experiments from the MICRO 2023 paper `Rigorous Evaluation of Computer Processors with Statistical Model Checking`.


## Instructions

These instructions are all that is required to replicate our results. Each directory within this repository contains instructions to replicate its contents as well.

A modified version of gem5 is included, along with a Docker container in which it runs correctly. Detailed instructions to replicate each are contained within the corresponding directory.

The same is done with the PARSEC benchmark suite. It is ready to execute within a disk image that will be read in by gem5.

While for the paper all gem5 experiments were run on a cluster, this artifact will contain a docker container to do so on a small scale on a local machine. Instructions are included for how to run these experiments on a cluster, as that will require gem5 compilation for the specific machines.

Both raw and extracted results are included in this repository. A local installation of SPA allows its analysis. Further plotting code is included to exactly reproduce the figures in the paper.


### Docker Image

The following Docker setup instructions result in a container that has both the gem5 binaries with random latencies and SPA. It is set up to run gem5 as was done to gather all results. It also contains all relevant SPA code with direct ways to create the figures. In order to view the figures, it is easiest to connect the docker container to a shared directory with the hots system. Alternatively, install the Conda environment and run the experimental figure code locally. Please see the gem5 section below for a description of how the gem5 executable was modified and built.

Prerequisite: install Docker.

```bash
cd spa-artifact
docker build -t spa-builder .
docker run --name spa-container --mount type=bind,source=./docker-share,destination=/shared -it spa-builder bash

# Here, you should be within the docker container. First, install conda
bash Miniconda3-py38_23.5.2-0-Linux-x86_64.sh

# Immediately activate it
conda activate

# Create the SPA environment and activate it
conda env create -f environment.yml
conda activate spa
```

### Downloading Ubuntu Image and Kernel

In order to run gem5, it requires a kernel and ubuntu image. Downloading the kernel is easy. We'll need to slightly modify the ubuntu image to replace some files with our own.

Download the kernel and image, within the shared directory, either outside or within the Docker container:

```bash
cd ubuntu-images/kernel/
wget http://dist.gem5.org/dist/v22-1/kernels/x86/static/vmlinux-5.4.49

cd ubuntu-images/disk/
wget http://dist.gem5.org/dist/v22-1/images/x86/ubuntu-18-04/parsec.img.gz

gzip -d parsec.img.gz
mv parsec.img x86-ubuntu-18_04-parsec
```

Next, we will need to mount the image and replace the parsec code with our custom hooks which work with gem5. For the rest of this section, we refer the read `docs/parsec-instructions.md` for more detail.

### gem5 Checkpointing

Checkpoints have already been created for convenience. More detail on checkpointing in gem5 can be found in `docs/gem5-instructions.md`, with associated files found in `docs/checkpointing/`.


### Running Experiments Using gem5

The docker image contains a Python script to run 5 iterations of the PARSEC benchmark `ferret`. Any more than that will take a huge amount of time. In the docker container, run the following:

```bash
cd /shared/python-runners/
python meta-runner.py
```

In order to generate meaningful amounts of data, we ran gem5 on a cluster. Instructions for how to do so are included below. This should run just the ROI for the `ferret` benchmark. Be advised that on a laptop this may take upwards of 12 hours.


## gem5 Executables

We include the pre-compiled gem5 executables. If there is any trouble with them, please refer to `docs/gem5-instructions.md`, especially if it is needed to re-compile them.

### Gettings Data From Experiments

gem5 will generate results to its specified output directory. We will use a modified script from `spa/util/convert_raw_results_to_csv.py` to choose the results that will be read in the property of interest and convert it into CSVs.

Here, we use a ready-made script to read in the metric `L1 cache misses / 1k instructions` by using the script

```bash
cd /shared/python-runners/
python convert-gem5-results-to-csv.py
```

This will create a CSV which contains the data from the gem5 runs.


### Analyzing Data

To analyze data, we include the experimental data results as CSVs from collecting gem5 run data. The result CSVs are duplicated in both the Docker container and in this repository. If you plan to run SPA in the Docker container, skip ahead to the section `Reproducing Results`. Otherwise, install SPA in the next section.


### Installing SPA Locally

Prerequisites:
* Install `conda`

We provided a conda environment file to set up the correct environment. The SPA package is installed locally using `pip`. This is the recommended installation on your normal working machine.

```shell
$ git clone git@github.com:filipmazurek/spa-artifact.git
$ cd spa-artifact/
$ conda env create -f environment.yml
$ conda activate spa
```

Note that it is not required to use conda. It is entirely possible to use `pip` to install everything.


### Reproducing Results

The following Python scripts will generate the data used in the plots as found in the paper. These scripts, along with the CSV data, are duplicated both in the repository and in the Docker container. For ease of use, we recommend directly running them in the Docker container and saving them to a shared directory to view on your local machine. Only figures 1 and 2 only create a plot. The remaining scripts will print to the console in order to directly verify the results without needing to visualize them. Note that the code for figures 6-11 only uses 100 trials for quick results (as opposed to 1000 in the paper). Figure 12 code only averages over 10 random seeds, and will save a figure.

```bash
conda activate spa
cd shared/python-runners
python figure-1.py
...
```


## Repository Contents

The following is descriptions for all other files in this repository. Each subsection will contain further information on what is contained within each directory, or will direct you to more detailed documentation.


### SPA

`spa/`

This package contains all required code to run SPA and create confidence intervals. It is installed locally as part of the conda environment (see the above section `Installing SPA Locally`).

NOTE: this is an unpolished implementation of SPA. A more polished version will be available prior to MICRO 2023.


#### SPA Usage

The best way to use SPA is within Python scripts for data analysis. After following the instructions in the section `Installing SPA`:

```python
# Function to actually run SPA
from smc.spa_frontend.spa import run_frontend
# Function to read in the CSV
from smc.util.csv_reader import read_data

args = argparse.Namespace
# The default property. As described in Table 1
args.property = ['ThresholdProperty']
# ThresholdProperty requires only 1 data source
args.data_source_2 = None
# Run full SPA, to find the CI
args.smc_only = False
# Chosen search granularity. None will auto-choose a suitable value
args.granularity = None
# Goal proportion value to search for. Must be between 0 and 1
args.proportion = 0.9
# Desired confidence. Must be between 0 and 1
args.confidence = 0.9
# Optional hint for where the value of interest might be
args.search_start_point = None
# Using linear search right now. Set an upper bound on elements searched
args.iteration_limit = 50000
# Only used for SMC with no CI finding
args.threshold = None
# Must be set to True for CI finding
args.continuous = True

# Give a new data source argument to the argparser
# Read in all data to analyze
args.data_source = read_data('path/to/file.csv')
# Run SPA
results = run_frontend(args)
spa_ci_low, spa_ci_high = (results[3], results[4])
```

Please excuse the poor naming. This will be fixed when the package is ready to be released.


### Extracted Data

`data/csv/`

This data has been extracted by the features of interest using the utility `util/convert_raw_results_to_csv.py` from all the raw run data gathered on the cluster.


### gem5

`gem5/`

NOTE: specific instructions for how to build gem5 with random latencies is described in: `gem5-modifidcations.md`.

Cloned from `https://github.com/gem5/gem5/tree/v22.1.0.0`. Note the version, `v22.1.0`.

It has already been modified to introduce random delays in the caches. This gem5 has been built for an x86 system.

It is possible to directly copy this directory to another system, ensure that the system has all required libraries installed, and build it. This version of gem5 is only modified to have random cache latencies in the Ruby memory system.


### Disk Image

NOTE: the disk and image downloads may be found in this json file, used by gem5-resources: [resources](https://resources.gem5.org/resources.json). These are the paths looked up through the Python code.

The disk image used for gem5 is a downloaded Ubuntu 18.04 image from gem5-resources. It can be easily downloaded from this [disk link](http://dist.gem5.org/dist/v22-1/images/x86/ubuntu-18-04/parsec.img.gz)

Or by the python script

```python
from gem5.resources.resource import Resource
disk_image=Resource(resource_name='x86-parsec')

```


### Kernel Binary

Like above the kernel image may be downloaded from `https://gem5.googlesource.com/public/gem5-resources/+/refs/tags/v22.0.0.2/src/linux-kernel/`

or downloaded using the Python script

```python
from gem5.resources.resource import Resource
disk_image=Resource(resource_name='x86-linux-kernel-5.4.49')
```


### PARSEC

Detailed instructions for how to compile the PARSEC benchmarks for gem5 can be read in this repository at `docs/parsec-instructions.md`


### gem5 instructions

Detailed instructions for how to compile gem5 with injected random latencies can be found in the file `docs/gem5-instructions.md`.

To run gem5 on a cluster with SLURM, we include the following scripts as examples:

- `docs/slurm-runners/gem5-builder.sh`: This script allows compiling gem5. To avoid compiling on the login node.
- `docs/slurm-runners/slurm-runner.sh`: This script starts running gem5 as a batch job. It starts a Python script and passes in an argument for which execution it is.
- `docs/slurm-runners/python-parsec-runner.py`: The Python script takes in the execution number from the SLURM batch job and determines what to run.


### Potential Bugs

I ran into a few issues that kept me from doing things exactly how I'd wanted to.

* Building gem5 is sometimes met with a `Python installation not found` error. I've run in to this twice, and I suspect it happens after building PARSEC within the same environment. Something about the installed libraries and process might lead to losing some link to the 3.6+ installation. This is likely because I was not careful enough about my installed packages. I'm pretty sure can be fixed with a simple linking command.

* I had a lot of trouble using the gem5 Resources link (`https://gem5.googlesource.com/public/gem5-resources/+/refs/tags/v22.0.0.2/src/x86-ubuntu/`) to build my own disk image using Packer (used to be fine, but again I suspect some poor library interactions). Instead, I ended up going with a gem5 resources download of a pre-built x86 system. It happens to be Ubuntu 18.04.

* Because of trouble building gem5 after PARSEC, I've decided to have all PARSEC builds in a contained environment. I used Docker for this purpose. Furthermore, I had to use a Docker container with Ubuntu 18.04 to match the Ubuntu disk downloaded from gem5 resources.

* The included example scripts for gem5 actually have a runscript for PARSEC benchmarks, along with hooks that lets the user specify behavior when entering/exiting the ROI. I would love to use this. However, I wanted to place checkpoints at
  1. OS boot and
  2. at the ROI entrance

Because I wanted to run the ROI using the `O3CPU` and Ruby memory. Everything that came before would be much easier to simulate using the `AtomicCPU` and no chaches. I didn't want to spend time building a `MOESI_hammer` memory system in the example script (because that's needed to create checkpoints), so instead I opted to use the old `fs.py` example script.


### Doing Things an Easier Way?

`gem5/configs/example/gem5_library/x86-parsec-benchmarks.py`

This script contains everything needed for this experiment. It will auto-download the kernel as well as the Ubuntu disk image pre-loaded with the PARSEC benchmark. There was just one problem with it: I am not familiar enough with the "new" way of writing gem5 instructions.

A reminder: overall goal is to simulate the PARSEC ROI with a detailed CPU and Ruby memory system. This (ideally) requires
1. simulate OS boot using fast CPU and no memory simulation
2. simulate the beginning of the PARSEC benchmark (data load, etc) in the same way
3. simulate the ROI with a detailed CPU and Ruby memory

This requires taking checkpoints (only possible using the `MOESI_hammer` protocol) and then successfully restoring them with a more detailed CPU. It would be easiest to just modify this script to be able to do all that. Unfortunately, I decided that it wasn't worth the time to modify the script and to figure out how to create a memory system (or lack of one) that would work with the `MOESI_hammer` protocol.

This could be used as future work in order to more quickly set up gem5 data collection.
