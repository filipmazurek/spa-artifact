#
# DO NOT EDIT THIS FILE!
# File automatically generated by
#   /shared/gem5/src/mem/slicc/symbols/StateMachine.py:295
#

from m5.params import *
from m5.SimObject import SimObject
from m5.objects.Controller import RubyController

class Directory_Controller(RubyController):
    type = 'Directory_Controller'
    cxx_header = 'mem/ruby/protocol/Directory_Controller.hh'
    cxx_class = 'gem5::ruby::Directory_Controller'
    directory = Param.RubyDirectoryMemory("")
    probeFilter = Param.RubyCache("")
    from_memory_controller_latency = Param.Cycles((2), "")
    to_memory_controller_latency = Param.Cycles((1), "")
    probe_filter_enabled = Param.Bool(("False"), "")
    full_bit_dir_enabled = Param.Bool(("False"), "")
    forwardFromDir = Param.MessageBuffer("")
    responseFromDir = Param.MessageBuffer("")
    dmaResponseFromDir = Param.MessageBuffer("")
    unblockToDir = Param.MessageBuffer("")
    responseToDir = Param.MessageBuffer("")
    requestToDir = Param.MessageBuffer("")
    dmaRequestToDir = Param.MessageBuffer("")
    triggerQueue = Param.MessageBuffer("")
    requestToMemory = Param.MessageBuffer("")
    responseFromMemory = Param.MessageBuffer("")
