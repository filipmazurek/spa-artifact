/**
 * DO NOT EDIT THIS FILE!
 * File automatically generated by
 *   build_tools/sim_object_param_struct_hh.py:235
 */

#ifndef __PARAMS__X86EmuLinux__
#define __PARAMS__X86EmuLinux__

namespace gem5 {
namespace X86ISA {
class EmuLinux;
} // namespace X86ISA
} // namespace gem5

#include "params/SEWorkload.hh"

namespace gem5
{
struct X86EmuLinuxParams
    : public SEWorkloadParams
{
    gem5::X86ISA::EmuLinux * create() const;
};

} // namespace gem5

#endif // __PARAMS__X86EmuLinux__
