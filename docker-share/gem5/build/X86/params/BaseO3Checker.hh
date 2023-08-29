/**
 * DO NOT EDIT THIS FILE!
 * File automatically generated by
 *   build_tools/sim_object_param_struct_hh.py:235
 */

#ifndef __PARAMS__BaseO3Checker__
#define __PARAMS__BaseO3Checker__

namespace gem5 {
namespace o3 {
class Checker;
} // namespace o3
} // namespace gem5

#include "params/CheckerCPU.hh"

namespace gem5
{
struct BaseO3CheckerParams
    : public CheckerCPUParams
{
    gem5::o3::Checker * create() const;
};

} // namespace gem5

#endif // __PARAMS__BaseO3Checker__
