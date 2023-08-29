/**
 * DO NOT EDIT THIS FILE!
 * File automatically generated by
 *   build_tools/sim_object_param_struct_hh.py:235
 */

#ifndef __PARAMS__X86ACPIMadt__
#define __PARAMS__X86ACPIMadt__

namespace gem5 {
namespace X86ISA {
namespace ACPI {
namespace MADT {
class MADT;
} // namespace MADT
} // namespace ACPI
} // namespace X86ISA
} // namespace gem5
#include <cstddef>
#include "base/types.hh"
#include <cstddef>
#include "base/types.hh"
#include <vector>
#include "params/X86ACPIMadtRecord.hh"

#include "params/X86ACPISysDescTable.hh"

namespace gem5
{
struct X86ACPIMadtParams
    : public X86ACPISysDescTableParams
{
    gem5::X86ISA::ACPI::MADT::MADT * create() const;
    uint32_t flags;
    uint32_t local_apic_address;
    std::vector< gem5::X86ISA::ACPI::MADT::Record * > records;
};

} // namespace gem5

#endif // __PARAMS__X86ACPIMadt__