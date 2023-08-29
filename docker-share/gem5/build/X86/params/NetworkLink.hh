/**
 * DO NOT EDIT THIS FILE!
 * File automatically generated by
 *   build_tools/sim_object_param_struct_hh.py:235
 */

#ifndef __PARAMS__NetworkLink__
#define __PARAMS__NetworkLink__

namespace gem5 {
namespace ruby {
namespace garnet {
class NetworkLink;
} // namespace garnet
} // namespace ruby
} // namespace gem5
#include <cstddef>
#include "base/types.hh"
#include <cstddef>
#include "base/types.hh"
#include <vector>
#include "base/types.hh"
#include <cstddef>
#include "base/types.hh"
#include <cstddef>
#include "base/types.hh"
#include <cstddef>
#include "base/types.hh"

#include "params/ClockedObject.hh"

namespace gem5
{
struct NetworkLinkParams
    : public ClockedObjectParams
{
    gem5::ruby::garnet::NetworkLink * create() const;
    int link_id;
    Cycles link_latency;
    std::vector< int > supported_vnets;
    int vcs_per_vnet;
    int virt_nets;
    uint32_t width;
};

} // namespace gem5

#endif // __PARAMS__NetworkLink__