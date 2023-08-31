# SPA Artifact

This repository consists of all required code, data, and instructions required to replicate the experiments from the MICRO 2023 paper `Rigorous Evaluation of Computer Processors with Statistical Model Checking`.


## Instructions

These instructions will allow the reader to replicate experimental results. More detailed instructions for how to recreate each precompiled binary are found in the `docs/` directory.

We include a modified version of gem5, a modified version of the PARSEC benchmark, pre-collected experiment results, the SPA code to analyze them, and Docker instructions to run it all.

While for the paper all gem5 experiments were run on a cluster, this artifact contains instructions to to do so on a small scale on a local machine. Instructions are included for how to run these experiments on a cluster in `docs`.


### Docker Image

The following Docker setup instructions result in a container that has both the gem5 binaries with random latencies and SPA. It is set up to run gem5 as was done to gather all results. It also contains all relevant SPA code with direct ways to create the figures. To view the figures, it is easiest to connect the docker container to a shared directory with the hots system. Alternatively, install the Conda environment and run the experimental figure code locally. Please see the gem5 section below for a description of how the gem5 executable was modified and built.

Prerequisite: Install Docker.

```bash
cd spa-artifact/
bash ./artifact-bash-scripts/set-up-docker.sh

# Here, you should be within the docker container.
# First, install conda with default options
cd /shared/
bash ./in-docker-bash-scripts/set-up-conda.sh

# Use conda with the bash shell
eval "$(/root/miniconda3/bin/conda shell.bash hook)"

conda activate spa
```

### Downloading Ubuntu Image and Kernel

To run gem5, it requires a kernel and ubuntu image. Downloading the kernel is easy. We'll need to slightly modify the ubuntu image to replace some files with our own.

Download the kernel and image, within the shared directory (either outside or within the Docker container):

```bash
cd /shared/
bash ./in-docker-bash-scripts/download-disk.sh
```

Next, we will need to mount the image and replace the parsec code with our custom hooks which work with gem5.


### gem5 PARSEC Binaries

In this section, we will copy our precompiled `ferret` binary into the disk image. For detail on how this was created, refer to `docs/parsec-instructions.md`.

```bash
cd /shared/
bash ./in-docker-bash-scripts/copy-parsec-binaries.sh
```


## gem5 Executables and Ceckpoints

We include pre-compiled gem5 executables and have also created checkpoints. Details can be found in `docs/gem5-instructions.md`.


### Running Experiments Using gem5

The docker image contains a Python script to run 5 iterations of the PARSEC benchmark `ferret`. Any more than that will take a huge amount of time. In the docker container, run the following:

```bash
cd /shared/python-runners/

chmod 777 /shared/gem5/build/X86/gem5-mesi.fast
python meta-runner.py
```

This will run the ROI for the `ferret` benchmark. Be advised that on a laptop this may take upwards of 12 hours.


### Gettings Data From Experiments

gem5 will generate results to its specified output directory. We will use a modified script from `spa/util/convert_raw_results_to_csv.py` to choose the results that will be read in the property of interest and convert it into CSVs.

Here, we use a ready-made script to read in the metric `L1 cache misses / 1k instructions`

```bash
cd /shared/python-runners/
python convert-gem5-results-to-csv.py
```

This will create a CSV which contains the data from the gem5 runs.


### Analyzing Data

To analyze data, we include the experimental data results as CSVs from collecting gem5 run data. If you plan to run SPA in the Docker container, skip ahead to the section `Reproducing Results`.


### Reproducing Results

The following Python scripts will generate the data used in the plots as found in the paper. These scripts, along with the CSV data, are duplicated both in the repository and in the Docker container. For ease of use, we recommend directly running them in the Docker container and saving them to a shared directory to view on your local machine. Only figures 1 and 2 only create a plot. The remaining scripts will print to the console to directly verify the results without needing to visualize them. Note that the code for figures 6-11 only uses 100 trials for quick results (as opposed to 1000 in the paper). Figure 12 code only averages over 10 random seeds, and will save a figure.

```bash
cd /shared/paper-figures/
python figure-1.py
...
python figure-12.py
```
