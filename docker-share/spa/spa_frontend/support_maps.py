PROPERTIES_MAP = {
    'ThresholdProperty': {'module': 'smc.smc_engine.property_specification',
                          'class': 'ThresholdProperty'},
    'RatioHyperproperty': {'module': 'smc.smc_engine.property_specification',
                           'class': 'RatioHyperproperty'},
}
"""List of available properties and hyperproperties."""

PROPERTIES_DESCRIPTIONS = {
    'ThresholdProperty': 'Property. Tests if `metric > threshold` (or <). Optional second argument for which equality '
                         'sign to use.',
    'RatioHyperproperty': 'Hyperproperty. Tests if `metric_a / metric_b > threshold`. Optional second argument for '
                          'which equality sign to use. Used to find speedup.'
}
"""Descriptions of available properties and hyperproperties."""

DATA_SOURCE_DESCRIPTIONS = {
    'csv': 'Any CSV file which has integer or floating point data. Optionally add a format argument (default: excel).',
    'gem5 output': 'Any given directory will assume to have default-style gem5 output. The parser will look for all '
                   'files named "stats.txt" within the directory. Requires a second argument for the field label.',
    'RandomIntegers': 'Given this key, random integers will be generated. Requires two more arguments, the mean and '
                      'std of the random numbers.'
}
"""List of available data sources and their descriptions."""

