import numpy as np
import math
import operator
from typing import Union

from smc.smc_engine.data_generator import DataGenerator
from smc.smc_engine.model_checker import HPSTLAlgorithm
from smc.smc_engine.property_specification import BaseProperty, BaseHyperProperty

_T_NUMBER = Union[int, float]
_T_PROPERTY = Union[BaseProperty, BaseHyperProperty]


class SPAException(Exception):
    """Exception for all SPA-related errors"""
    pass


class SpaRuntime:
    """Defines all methods to find a range of the satisfied SMC property parameter."""

    def __init__(self, property_: _T_PROPERTY, data_generators: list[DataGenerator], granularity: float = None,
                 proportion: float = 0.9, confidence: float = 0.9, iteration_limit: int = 1000,
                 search_start_point: float = None, continuous: bool = False):
        self.property_ = property_
        self.data_generators = data_generators
        self.granularity = granularity
        self.proportion = proportion
        self.confidence = confidence
        self.iteration_limit = iteration_limit
        self.search_start_point = search_start_point
        self.continuous = continuous

        # Input the correct number of generators to the property
        if self.property_.NUM_SOURCES == 1:
            assert len(self.data_generators) == 1, 'Properties require one data source.'
            self.property_.add_generator(*self.data_generators)
        elif self.property_.NUM_SOURCES == 2:
            assert len(self.data_generators) == 2, 'Hyperproperties require two data sources.'
            self.property_.add_generator(*self.data_generators)

    @staticmethod
    def round_to(val, precision):
        """Rounding function to the nearest multiple of the input precision"""
        return round(val / precision) * precision

    def create_new_threshold_checker(self, property_param):
        # Set the new threshold
        self.property_.threshold = property_param
        # Prepare the data generators
        self.property_.reset_generator()
        # Create new SMC checker
        return HPSTLAlgorithm(self.property_)

    def single_direction_search(self, starting_point: _T_NUMBER, direction_operator):
        """Use SMC with new parameters until the goal is hit.
        e.g. Increase the speedup parameter until hit a `False` result
        :param starting_point: Starting value for property testing
        :param direction_operator: add or sub, for searching increasing or decreasing values
        :returns : A dictionary of SMC results. Key: tested parameter, Value: SMC result
        """
        assert (direction_operator is operator.add) or (direction_operator is operator.sub), \
            'direction operator must be either add or sub'

        res_dict = {}
        conf_dict = {}
        lean_dict = {}
        param = starting_point
        iteration = 0

        # Pick the correct goal bool - to make sure that the search converges to a result
        if direction_operator is operator.add:
            goal_bool = self.property_.get_high_threshold_outcome()
        else:
            goal_bool = not self.property_.get_high_threshold_outcome()

        while True:
            # Run SMC to find if the result is True, False, or inconclusive
            smc_obj = self.create_new_threshold_checker(param)
            res, conf, _, _, _, lean_list = smc_obj.verify(self.proportion, self.confidence, self.continuous)
            res_dict[param] = res
            conf_dict[param] = conf
            lean_dict[param] = lean_list[-1]

            # Stop when the goal state is hit
            if res is goal_bool:
                break

            if iteration > self.iteration_limit:
                raise SPAException('Reached search iteration limit without finding the goal SMC result. '
                                   'Consider raising the iteration limit and ensure that the property operation and '
                                   'high threshold outcome is set correctly.')

            # Update parameters for hte next iteration
            param = self.round_to(direction_operator(param, self.granularity), self.granularity)
            iteration += 1

        return res_dict, conf_dict, lean_dict

    def search_loop(self):
        """
        Find the boundary for where the SMC result becomes opposite of itself
        :return: The upper and lower bounds on this region
        """
        # Get many data points to calculate the mean
        num_data_points = 100
        generator_0 = self.data_generators[0]
        vals_0 = generator_0.get_data_list(num_data_points)
        if self.property_.NUM_SOURCES == 2:
            generator_1 = self.data_generators[1]
            vals_1 = generator_1.get_data_list(num_data_points)

        # Find the mean starting point using the property's operation method
        if self.property_.NUM_SOURCES == 2:
            vals = [self.property_.data_operation(a, b) for a, b in zip(vals_0, vals_1)]
        else:
            vals = [self.property_.data_operation(a) for a in vals_0]
        
        # Granularity may not be set. Calculate one that is the nearest order of magnitude to 0.1% of the mean value
        # Uses ceil for a more conservative estimate
        if self.granularity is None:
            self.granularity = 10 ** math.ceil(math.log10(np.quantile(vals, 1-self.proportion) / 1000))

        if self.search_start_point is None:
            self.search_start_point = self.round_to(np.quantile(vals, 1-self.proportion), self.granularity)

        # Find the goal SMC result, begin at starting point and increase the parameter until the goal is found
        res_dict, conf_dict, lean_dict = self.single_direction_search(self.search_start_point, operator.add)
        new_start = self.round_to(self.search_start_point - self.granularity, self.granularity)
        res_dict_decr, conf_dict_decr, lean_dict_decr = self.single_direction_search(new_start, operator.sub)

        # Combine the two single-direction search results into a single dictionary
        res_dict.update(res_dict_decr)
        conf_dict.update(conf_dict_decr)
        lean_dict.update(lean_dict_decr)

        # Sort dictionary by its keys (increasing parameter values)
        res_dict = dict(sorted(res_dict.items()))
        conf_dict = dict(sorted(conf_dict.items()))
        lean_dict = dict(sorted(lean_dict.items()))

        # print(res_dict)

        # Separate the result dictionary into one where the result was true and one where the results are all false
        true_result_dict = dict(filter(lambda pair: pair[1], res_dict.items()))
        false_result_dict = dict(filter(lambda pair: not pair[1], res_dict.items()))
        false_result_dict = {k:v for k,v in false_result_dict.items() if v is not None}

        # Self-contained check for the boundary. Accounts for the opposing truth values if the property uses > or <
        max_true = max(true_result_dict.keys())
        min_true = min(true_result_dict.keys())
        max_false = max(false_result_dict.keys())
        min_false = min(false_result_dict.keys())

        if max_true < min_false:
            spa_lower_bound = max_true
            spa_upper_bound = min_false
        else:
            spa_lower_bound = min_true
            spa_upper_bound = max_false

        return spa_lower_bound, spa_upper_bound, res_dict, conf_dict, lean_dict

    def full_analysis(self):
        # TODO: only print when desired
        spa_lower_bound, spa_upper_bound, res_dict, conf_dict, lean_dict = self.search_loop()

        # print('===========================')
        # print('=       SPA RESULTS       =')
        # print('===========================')
        # print('Hypothesis:')
        # print(f'    Proportion:  {self.proportion}')
        # print(f'    Confidence:  {self.confidence}')
        # print('Parameters:')
        # print(f'    Granularity: {self.granularity}')
        # print('Result:')
        # print(f'    The property is between {self.round_to(spa_lower_bound, self.granularity)} and '
        #       f'{self.round_to(spa_upper_bound, self.granularity)}')

        return [self.proportion, self.confidence, self.granularity, self.round_to(spa_lower_bound, self.granularity), self.round_to(spa_upper_bound, self.granularity), res_dict, conf_dict, lean_dict]


def run(property_: _T_PROPERTY, data_generators: list[DataGenerator], proportion: float = 0.9, confidence: float = 0.9,
        granularity: float = None, search_start_point: float = None, iteration_limit: int = 1000, continuous: bool = False) -> list:
    # Use the given property through dynamic import of appropriate module
    spa = SpaRuntime(property_=property_, proportion=proportion, confidence=confidence, data_generators=data_generators,
                     granularity=granularity, search_start_point=search_start_point, iteration_limit=iteration_limit, continuous=continuous)
    return spa.full_analysis()
