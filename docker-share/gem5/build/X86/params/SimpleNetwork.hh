/**
 * DO NOT EDIT THIS FILE!
 * File automatically generated by
 *   build_tools/sim_object_param_struct_hh.py:235
 */

#ifndef __PARAMS__SimpleNetwork__
#define __PARAMS__SimpleNetwork__

namespace gem5 {
namespace ruby {
class SimpleNetwork;
} // namespace ruby
} // namespace gem5
#include <cstddef>
#include "base/types.hh"
#include <cstddef>
#include "base/types.hh"
#include <vector>
#include "base/types.hh"
#include <vector>
#include "base/types.hh"

#include "params/RubyNetwork.hh"

namespace gem5
{
struct SimpleNetworkParams
    : public RubyNetworkParams
{
    gem5::ruby::SimpleNetwork * create() const;
    int buffer_size;
    int endpoint_bandwidth;
    std::vector< int > physical_vnets_bandwidth;
    std::vector< int > physical_vnets_channels;
};

} // namespace gem5

#endif // __PARAMS__SimpleNetwork__
