import abc
import csv
import numpy as np
import os
from typing import Union

_T_NUMBER = Union[int, float]


class DataGeneratorException(Exception):
    """Exception generated when the DataGenerator runs out of data"""
    pass


class DataGenerator(abc.ABC):
    """Generate data from some source. This should be treated as a thin wrapper.
    Meant to be wrapped around data sources such as archived data or random number generators.
    """

    def __init__(self):
        # A tuple where the first item is a list of all items found so far and the second is the "current item".
        # Don't have to re-read the source on repeated SMC runs in SPA with stored data.
        self.created_data = ([], 0)

    @abc.abstractmethod
    def _get_next_data_point(self):
        pass

    def next_data_point(self) -> _T_NUMBER:
        """Get the next single data point from the source

        :return: A single data point of the specified type
        """
        # If the data was previously obtained, return it
        data_list = self.created_data[0]
        index = self.created_data[1]
        if len(data_list) > index:
            self.created_data = (data_list, index + 1)
            return data_list[index]
        else:
            # Otherwise, read the next data point from the data source and save it to the data list
            next_data = self._get_next_data_point()
            self.created_data = (data_list + [next_data], index + 1)
            return next_data

    def reset_generator(self):
        """Make the generator appear as it was originally. On the next iteration, will return the data it already read
        """
        self.created_data = (self.created_data[0], 0)

    def get_data_list(self, max_data_points: int = 100) -> list[_T_NUMBER]:
        """Return the list of data - all that was read from the data source from the beginning

        :param max_data_points: Requested length of the data list
        :return: List of data from the generator, including what was previously generated
        """
        # Find how much more data needs to be read
        more_data = max_data_points - len(self.created_data[0])
        more_data = max(more_data, 0)
        try:
            for _ in range(more_data):
                data = self._get_next_data_point()
                self.created_data = (self.created_data[0] + [data], self.created_data[1])
        except DataGeneratorException:
            # If there is no more data to read, fall through and return all the data from the generator
            pass

        return self.created_data[0]


class NormalDistributionGenerator(DataGenerator, abc.ABC):
    """Creates random data with the specified normal distribution"""

    def __init__(self, center: _T_NUMBER, std_dev: _T_NUMBER):
        """
        :param center: Center of the standard distribution
        :param std_dev: Standard deviation
        """
        super(NormalDistributionGenerator, self).__init__()
        self.center = center
        self.std_dev = std_dev


class NormalDistributionFloatGenerator(NormalDistributionGenerator):
    """Creates random *float* data with the specified normal distribution"""

    def _get_next_data_point(self) -> float:
        data = -1
        # Ensure that the data point returned is a positive number (technically not a normal distribution,
        #   but preserves reality
        while data < 0:
            data = np.random.normal(self.center, self.std_dev)
        return data


class NormalDistributionIntGenerator(NormalDistributionFloatGenerator):
    """Creates random *integer* data with the specified normal distribution"""

    def _get_next_data_point(self) -> int:
        return int(round(super(NormalDistributionIntGenerator, self)._get_next_data_point()))


class DirectValueGenerator(DataGenerator):
    """Gives back the values that are given to it. Useful to input custom lists of data, or data that was already
    read out of some file
    """

    def __init__(self, data_list: list[_T_NUMBER]):
        super(DirectValueGenerator, self).__init__()
        # Override read all data into the created_data list
        self.created_data = (data_list, 0)

    def _get_next_data_point(self) -> _T_NUMBER:
        # If this method is called, the generator has run out of data
        raise DataGeneratorException('Ran out of data to get')


class CSVValueGenerator(DataGenerator):
    """Reads through CSV data and returns the data."""

    def __init__(self, filepath: str, dialect: str = 'excel'):
        """
        :param filepath: path of the CSV file containing all data
        :param dialect: format of the CSV file
        """
        super(CSVValueGenerator, self).__init__()
        self.filepath = os.path.abspath(filepath)

        # Read in all data from the CSV and save it into the created_data list
        # FIXME: move this to the _get_next_data_point method if there is any use for incremental csv reading
        all_data = []
        with open(self.filepath, 'r') as file:
            reader = csv.reader(file, dialect=dialect)
            for string_vals in reader:
                for val in string_vals:
                    # Deafult the type of data to float - should work whether using int or float
                    all_data.append(float(val))

        self.created_data = (all_data, 0)

    def _get_next_data_point(self) -> _T_NUMBER:
        # If this method is called, the generator has run out of data
        raise DataGeneratorException('Ran out of data to get')
