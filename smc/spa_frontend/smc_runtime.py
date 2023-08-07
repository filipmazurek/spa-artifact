from typing import Union

from smc.smc_engine.data_generator import DataGenerator
from smc.smc_engine.model_checker import HPSTLAlgorithm
from smc.smc_engine.property_specification import BaseProperty, BaseHyperProperty

_T_PROPERTY = Union[BaseProperty, BaseHyperProperty]


class SMCPropertyRunner:
    """Helper class to set up a property check using the HPSTL SMC algorithm"""

    def __init__(self, data_generators: list[DataGenerator], property_: _T_PROPERTY, probability: float = 0.9,
                 desired_conf: float = 0.9):
        self.prob = probability
        self.a_d = desired_conf

        # Add the data generators to the property
        if property_.NUM_SOURCES == 1:
            assert len(data_generators) == 1, 'Properties require one data source.'
            property_.add_generator(*data_generators)
        elif property_.NUM_SOURCES == 2:
            assert len(data_generators) == 2, 'Hyperproperties require two data sources.'
            property_.add_generator(*data_generators)
        self.property_ = property_

    def run(self):
        checker = HPSTLAlgorithm(self.property_)
        result, *_ = checker.verify(self.prob, self.a_d)
        return result


def run(property_: _T_PROPERTY, data_generators, proportion, confidence):
    # Use the given property through dynamic import of appropriate module
    smc = SMCPropertyRunner(data_generators, property_, proportion, confidence)
    result = smc.run()

    if result is None:
        result_str = 'There were not enough samples to reach a conclusion. Re-running with more samples or different ' \
                     'parameters may reach a conclusion'
    elif result is True:
        result_str = 'For the given parameters, the property is True'
    elif result is False:
        result_str = 'For the given parameters, the property is False'

    print('==========================')
    print('=       SMC RESULT       =')
    print('==========================')
    print('Hypothesis:')
    print(f'    Threshold: {property_.threshold}')
    print(f'    Proportion: {proportion}')
    print(f'    Confidence: {confidence}')
    print('Result:')
    print(f'    {result_str}')

    return [property_.threshold, proportion, confidence, result]
