/**
 * DO NOT EDIT THIS FILE!
 * File automatically generated by
 *   build_tools/sim_object_param_struct_hh.py:235
 */

#ifndef __PARAMS__Platform__
#define __PARAMS__Platform__

namespace gem5 {
class Platform;
} // namespace gem5
#include <cstddef>
#include "params/System.hh"

#include "params/SimObject.hh"

namespace gem5
{
struct PlatformParams
    : public SimObjectParams
{
    gem5::System * system;
};

} // namespace gem5

#endif // __PARAMS__Platform__
