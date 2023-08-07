import abc
import operator
from typing import Union

from smc.smc_engine.data_generator import DataGenerator

_T_NUMBER = Union[int, float]


class BaseSpecification(abc.ABC):
    """The most generic property class"""

    @abc.abstractmethod
    def check_sample_satisfy(self) -> bool:
        """Get a new data point(s) and check if it satisfies the property's condition"""
        pass


class GenericThresholdProperty(BaseSpecification, abc.ABC):
    """Generic (hyper)property class which requires the input of some threshold"""

    NUM_SOURCES = None
    """The expected number of data sources for the property"""

    def __init__(self, threshold: _T_NUMBER = None, op='>', high_threshold_outcome: bool = False):
        """
        :param threshold: The property's current threshold to check against. May be changed later.
        :param op: The comparison operator to use for the threshold comparison. '>' or '<'.
        :param high_threshold_outcome: The expected property result when checking against a high threshold.
        """
        self._threshold = threshold
        self._high_threshold_outcome = high_threshold_outcome
        if op == '>':
            self._comparison = operator.gt
        elif op == '<':
            self._comparison = operator.lt
        else:
            raise RuntimeError('Given operation for the property must be either `>` or `<`')

    @property
    def threshold(self) -> _T_NUMBER:
        return self._threshold

    @threshold.setter
    def threshold(self, threshold: _T_NUMBER):
        # TODO: logger info. Useful to know if threshold is changing within SMC checks
        self._threshold = threshold

    def get_high_threshold_outcome(self) -> _T_NUMBER:
        return self._high_threshold_outcome


class BaseProperty(GenericThresholdProperty, abc.ABC):
    """Template for checking any property that uses a single threshold value"""
    NUM_SOURCES = 1

    def add_generator(self, data_generator: DataGenerator) -> None:
        """Add a generator object to the property. Required for all satisfaction checks"""
        assert not hasattr(self, '_data_generator'), 'Cannot reassign a data generator'
        self._data_generator = data_generator

    def reset_generator(self) -> None:
        """Reset generator values. Used when wanting to start over the SMC algorithm."""
        self._data_generator.reset_generator()

    def check_sample_satisfy(self) -> bool:
        data = self._data_generator.next_data_point()
        return self._satisfies(data)

    def _satisfies(self, data_1: _T_NUMBER) -> bool:
        """Check that the sample satisfies the comparison against the threshold"""
        return self._comparison(self.data_operation(data_1), self._threshold)

    @staticmethod
    @abc.abstractmethod
    def data_operation(data: _T_NUMBER) -> _T_NUMBER:
        """The required operation on each data point before comparing it to the threshold"""
        pass


class ThresholdProperty(BaseProperty):
    """Property to directly check each data point against the specified threshold"""

    @staticmethod
    def data_operation(data: _T_NUMBER) -> _T_NUMBER:
        return data


class BaseHyperProperty(GenericThresholdProperty, abc.ABC):
    """Template for checking any hyperproperty against a single threshold value"""

    NUM_SOURCES = 2

    def add_generator(self, data_generator_1: DataGenerator, data_generator_2: DataGenerator):
        """Add generator objects to the property. Required for all satisfaction checks"""
        assert not hasattr(self, '_data_generator_1'), 'Cannot reassign a data generator'
        assert not hasattr(self, '_data_generator_2'), 'Cannot reassign a data generator'
        self._data_generator_1 = data_generator_1
        self._data_generator_2 = data_generator_2

    def reset_generator(self):
        """Reset generator values. Used when wanting to start over the SMC algorithm."""
        self._data_generator_1.reset_generator()
        self._data_generator_2.reset_generator()

    def check_sample_satisfy(self) -> bool:
        data_1 = self._data_generator_1.next_data_point()
        data_2 = self._data_generator_2.next_data_point()
        return self._satisfies(data_1, data_2)

    def _satisfies(self, data_1: _T_NUMBER, data_2: _T_NUMBER) -> bool:
        """Check that the ratio difference is greater than some specified threshold"""
        return self._comparison(self.data_operation(data_1, data_2), self._threshold)

    @staticmethod
    @abc.abstractmethod
    def data_operation(data_1: _T_NUMBER, data_2: _T_NUMBER) -> _T_NUMBER:
        pass


class RatioHyperproperty(BaseHyperProperty):
    """Comparison model to compare the ratios of two execution properties. Notably, this includes speedup."""

    @staticmethod
    def data_operation(data_1: _T_NUMBER, data_2: _T_NUMBER):
        return data_2 / data_1
