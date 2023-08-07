import os
import re


def create_seeds_in_file():
    """
    Creates a list of the desired number of seeds
    """
    num_seeds = 1000
    seed_length = 50
    filename = f'seeds_{num_seeds}-length_{seed_length}.txt'

    a = []

    for _ in range(num_seeds):
        a.append(os.urandom(seed_length))

    with open(filename, 'wb') as f:
        for s in a:
            f.write(s)


def read_seeds_from_file(filename: str):
    """
    Returns a list of seeds given a file of byte seeds
    """
    name_only = filename.split('/')[-1].split('.')[0]
    num_seeds, seed_length = re.findall('\d+', name_only)
    num_seeds = int(num_seeds)
    seed_length = int(seed_length)

    with open(filename, 'rb') as f:
        all_data = f.read()

    seeds = []

    for i in range(num_seeds):
        seeds.append(all_data[(i*seed_length):(seed_length*(i+1))])

    return seeds
