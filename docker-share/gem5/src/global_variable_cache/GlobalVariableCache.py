from m5.params import *
from m5.SimObject import SimObject

class GlobalVariableCache(SimObject):
    type = 'GlobalVariableCache'
    cxx_header = "global_variable_cache/global_variable_cache.hh"
    cxx_class = "gem5::GlobalVariableCache"
    inputSeed = Param.Int(0, "")