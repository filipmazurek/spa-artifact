import csv

def read_data(directory):
    with open(directory, 'r') as file:
        reader = csv.reader(file, dialect='excel')
        string_vals = reader.__next__()
    try:
        values = [int(s) for s in string_vals]
    except ValueError:
        values = [float(s) for s in string_vals]

    return values
