#!/usr/bin/env python3

import argparse
import importlib
import os.path
from typing import Optional, Union

import smc.spa_frontend.smc_runtime
import smc.spa_frontend.spa_runtime
from smc.smc_engine.data_generator import CSVValueGenerator, DataGenerator, DirectValueGenerator, NormalDistributionIntGenerator
from smc.smc_engine.model_checker import HPSTLAlgorithm
from smc.smc_engine.property_specification import BaseProperty, BaseHyperProperty
from smc.spa_frontend.support_maps import DATA_SOURCE_DESCRIPTIONS, PROPERTIES_DESCRIPTIONS, PROPERTIES_MAP

_T_PROPERTY = Union[BaseProperty, BaseHyperProperty]
_T_THRESHOLD_LIST = Optional[list[str]]


# TODO: decouple the property and generator creation from this frontend file
#   should be optional to give strings or the actual objects - but probably just the strings

class SPAException(Exception):
    """Exception for all SPA-related errors"""
    pass


def get_argparser():
    """Create argument parser used for the CLI"""
    parser = argparse.ArgumentParser(
        description='SMC Processor Analysis (SPA). Tool for investigating processor simulation results.',
        formatter_class=argparse.RawTextHelpFormatter)

    # Choice to do a full SPA range find or a single SMC run
    parser.add_argument('--smc-only', action='store_true',
                        help='Choice to whether to run only a single SMC run whose result may be True, False, or None '
                             '(when there is not enough data to reach a conclusion). Running single SMC (False option) '
                             'also requires filling out the --threshold argument. When this flag is not set, the '
                             'default is to run a full range-finding analysis.')

    # Set the threshold(s) for the SMC property. Only used when --range-finder is set to False
    parser.add_argument('-t', '--threshold', nargs='*',
                        help='Threshold value(s) required for the SMC property when --range-finder option is set to '
                             'False. ')

    # Data source help string
    data_source_help = ''
    for k, v in DATA_SOURCE_DESCRIPTIONS.items():
        data_source_help += f'{k}: {v}\n'
    # Data source and accompanying parameters
    parser.add_argument('-d', '--data-source', nargs='+', help=data_source_help)

    # Data source 2 parameters
    parser.add_argument('-s', '--data-source-2', nargs='*',
                        help='Second data source. Required when investigating hyperproperties.')

    # Property help string
    property_help = ''
    for k, v in PROPERTIES_DESCRIPTIONS.items():
        property_help += f'{k}: {v}\n'
    # Property to test, from the list available property classes
    parser.add_argument('-p', '--property', nargs='+', help=property_help)

    # Search granularity
    # Doubled '%%' is an escape sequence to recognize the % sign
    parser.add_argument('-g', '--granularity', type=float, default=None,
                        help='Search granularity for SPA. All results will be a multiple of this value. By default, '
                             'uses 0.1%% of the average value, rounded to the nearest order of magnitude.')

    # Proportion
    parser.add_argument('-f', '--proportion', type=float, default=0.9,
                        help='Proportion of results that must satisfy the property. Affects the minimum required '
                             'number of samples.')

    # Desired confidence
    parser.add_argument('-c', '--confidence', type=float, default=0.9,
                        help='Desired confidence for each SMC result. Affects the minimum required number of samples.')

    # Starting point for starting the search
    parser.add_argument('-r', '--search-start-point', type=float, default=None,
                        help='The starting point for SPA search. This may be optionally provided to help reduce the '
                             'number of search iterations (Note that a poor starting point may lead to more search '
                             'iterations). Default: automatically find the start search point.')

    # Iteration limit for SPA search
    parser.add_argument('-l', '--iteration-limit', type=int, default=1000,
                        help='Iteration limit for SPA search. A higher limit allows SPA to search for convergent SMC '
                             'solutions longer. If SPA still fails to converge even after raising the iteration limit, '
                             'consider changing the granularity and the search-start-point')

    parser.add_argument('--continuous', action='store_true',
                        help='Temp frontend holder')
    # TODO: add a logger
    # Adds verbosity arguments (-v, -q)
    # common_args.verbosity_args(parser)

    return parser


def create_generator(source: list) -> DataGenerator:
    # Find which data source is used and prepare it as a class
    if source[0] == 'RandomIntegers':
        assert (len(source) == 3), 'RandomIntegers requires a mean and std'
        return NormalDistributionIntGenerator(float(source[1]), float(source[2]))
    elif type(source) is list and (type(source[0]) is int or type(source[0]) is float):
        return DirectValueGenerator(source)
    elif os.path.isdir(source[0]):
        raise SPAException('Directory with raw gem5 output is not yet supported. Export all data to a csv first.')
    elif source[0].endswith('.csv'):
        return CSVValueGenerator(*source)
    else:
        raise SPAException(f'Data source must be one of the following: {list(DATA_SOURCE_DESCRIPTIONS.keys())}')


def create_property(prop: list[str], threshold_str_list: _T_THRESHOLD_LIST) -> _T_PROPERTY:
    # Find which property source is specified and prepare is as a class
    try:
        property_module = importlib.import_module(PROPERTIES_MAP.get(prop[0]).get('module'))
        property_class = getattr(property_module, PROPERTIES_MAP.get(prop[0]).get('class'))
    except AttributeError:
        raise SPAException(f'Property must be one of the following: {list(PROPERTIES_DESCRIPTIONS.keys())}')

    # Pass in all arguments for the property class. The first argument is threshold
    # The prop argument is a list of the property followed by parameters for the property
    if threshold_str_list is None:
        return property_class(None, *prop[1:])
    else:
        threshold = float(threshold_str_list[0])
        return property_class(threshold, *prop[1:])


def run_frontend(args):
    assert args.property is not None, 'A property is required'
    assert args.data_source is not None, 'A data source is required'

    # Create the property
    property_ = create_property(args.property, args.threshold)

    # Create the correct generators given the data
    generator_1 = create_generator(args.data_source)
    if args.data_source_2 is None:
        generators = [generator_1]
    else:
        generator_2 = create_generator(args.data_source_2)
        generators = [generator_1, generator_2]

    # Ensure that the correct number of sources was passed in to the property
    req_sources = property_.NUM_SOURCES
    assert len(generators) == req_sources, f'The property must be given {req_sources} data sources'

    # Check that there are enough data points to complete the requested SPA run
    min_num_samples = HPSTLAlgorithm.min_num_samples(proportion=args.proportion, confidence=args.confidence)
    min_samples_string = f'With parameters proportion={args.proportion} and desired confidence={args.confidence}, SPA' \
                         f'requires at least {min_num_samples} to converge.'
    assert len(generator_1.get_data_list(min_num_samples)) >= min_num_samples, \
        f'Not enough samples in the first data source. {min_samples_string}'
    if len(generators) > 1:
        assert len(generator_2.get_data_list(min_num_samples)) >= min_num_samples, \
            f'Not enough samples in the second data source. {min_samples_string}'

    # Option to run SMC algorithm without the range-finding SPA
    if args.smc_only:
        assert args.threshold is not None, 'When running with the smc-only option, must provide threshold values'
        return smc.spa_frontend.smc_runtime.run(property_=property_, data_generators=generators, proportion=args.proportion,
                                         confidence=args.confidence)
    else:
        return smc.spa_frontend.spa_runtime.run(property_=property_, proportion=args.proportion, confidence=args.confidence,
                                         data_generators=generators, granularity=args.granularity,
                                         iteration_limit=args.iteration_limit,
                                         search_start_point=args.search_start_point,
                                         continuous=args.continuous)


def main():
    """Entrypoint for SPA from the CLI"""
    args = get_argparser().parse_args()
    run_frontend(args)


if __name__ == "__main__":
    main()
