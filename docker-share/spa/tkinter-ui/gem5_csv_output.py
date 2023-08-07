#!/usr/bin/env python3

import argparse
from datetime import datetime
import os.path
import re

def get_argparser():
    """Create argument parser used for the CLI"""
    parser = argparse.ArgumentParser(
        description='Create CSV file of metric from raw gem5 output',
        formatter_class=argparse.RawTextHelpFormatter)
    
    # inputs = gem5 directory to crawl, filename to look for (stats.txt), metric key, destination directory
    parser.add_argument('-d', '--data-directory', help="Enter parent directory containing gem5 run outputs")

    parser.add_argument('-f', '--filename', type=str, default="stats.txt", help="Enter the generic file name that contains the gem5 metric of interest (default is stats.txt)")

    parser.add_argument('-k', '--key', type=str, default="simSeconds", help="Enter the metric key exactly as displayed in the output files")

    parser.add_argument('-o', '--output-filename', default=None, help="Enter where the output csv will be saved to (default is directory of util)")

    return parser

def run_frontend(args):
    assert args.data_directory is not None, 'A directory of raw gem5 outputs is required'
    assert os.path.isdir(args.data_directory), "Invalid data directory"

    regex = f'(?<={args.key})\s+(\d+(?:\.\d+)?)'
    results = []
    result_vals =[]
    csvtitle = ""

    if args.output_filename is None:
        csvtitle = args.key + "_gem5output_" + str(datetime.now().strftime('%Y%m-%d%H-%M%S')) + '.csv'
        
    else:
        csvtitle = args.output_filename
    
    path = args.data_directory
    file_list = []
    for root, dirs, files in os.walk(path):
        for file in files:
            file_list.append(root + "/" +file)
    file_list.sort(key=lambda x: os.path.getmtime(x))

    for path in file_list:
        if path.split("/")[-1] == args.filename:
            print(path)
            with open(path, 'r') as f:
                try:
                    value = re.search(regex, f.read())
                    value = float(value.group(0)) 
                except AttributeError:
                    continue

                results.append({'value': value, 'path': path})
                result_vals.append(value)
                    

    print(f'{len(result_vals)} gem5 outputs found')

    if len(result_vals) == 0:
        print("No records found - check directory, filename, or key")
    else:
        import csv
        with open(csvtitle, 'w') as file:
            writer = csv.writer(file, dialect='excel')
            writer.writerow(result_vals)
            print('Finished writing to ' + csvtitle)


def main():
    """Entrypoint for SPA from the CLI"""
    args = get_argparser().parse_args()
    run_frontend(args)


if __name__ == "__main__":
    main()
