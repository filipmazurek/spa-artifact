/**
 * DO NOT EDIT THIS FILE!
 * File automatically generated by
 *   build_tools/sim_object_param_struct_hh.py:235
 */

#ifndef __PARAMS__Gem5ToTlmBridgeBase__
#define __PARAMS__Gem5ToTlmBridgeBase__

namespace sc_gem5 {
class Gem5ToTlmBridgeBase;
} // namespace sc_gem5
#include <vector>
#include "base/types.hh"
#include "base/addr_range.hh"
#include <cstddef>
#include "params/System.hh"

#include "params/SystemC_ScModule.hh"

namespace gem5
{
struct Gem5ToTlmBridgeBaseParams
    : public SystemC_ScModuleParams
{
    std::vector< AddrRange > addr_ranges;
    gem5::System * system;
    unsigned int port_gem5_connection_count;
};

} // namespace gem5

#endif // __PARAMS__Gem5ToTlmBridgeBase__
