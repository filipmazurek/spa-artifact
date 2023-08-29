#
# DO NOT EDIT THIS FILE!
# File automatically generated by
#   /shared/gem5/src/mem/slicc/symbols/StateMachine.py:295
#

from m5.params import *
from m5.SimObject import SimObject
from m5.objects.Controller import RubyController

class L1Cache_Controller(RubyController):
    type = 'L1Cache_Controller'
    cxx_header = 'mem/ruby/protocol/L1Cache_Controller.hh'
    cxx_class = 'gem5::ruby::L1Cache_Controller'
    sequencer = Param.RubySequencer("")
    L1Icache = Param.RubyCache("")
    L1Dcache = Param.RubyCache("")
    L2cache = Param.RubyCache("")
    cache_response_latency = Param.Cycles((10), "")
    issue_latency = Param.Cycles((2), "")
    l2_cache_hit_latency = Param.Cycles((10), "")
    no_mig_atomic = Param.Bool(("True"), "")
    send_evictions = Param.Bool("")
    requestFromCache = Param.MessageBuffer("")
    responseFromCache = Param.MessageBuffer("")
    unblockFromCache = Param.MessageBuffer("")
    forwardToCache = Param.MessageBuffer("")
    responseToCache = Param.MessageBuffer("")
    mandatoryQueue = Param.MessageBuffer("")
    triggerQueue = Param.MessageBuffer("")