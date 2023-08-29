/**
 * DO NOT EDIT THIS FILE!
 * File automatically generated by
 *   build_tools/sim_object_param_struct_hh.py:235
 */

#ifndef __PARAMS__X86KvmCPU__
#define __PARAMS__X86KvmCPU__

namespace gem5 {
class X86KvmCPU;
} // namespace gem5
#include <cstddef>

#include "params/BaseKvmCPU.hh"

namespace gem5
{
struct X86KvmCPUParams
    : public BaseKvmCPUParams
{
    gem5::X86KvmCPU * create() const;
    bool useXSave;
};

} // namespace gem5

#endif // __PARAMS__X86KvmCPU__
