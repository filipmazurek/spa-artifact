/**
 * DO NOT EDIT THIS FILE!
 * File automatically generated by
 *   build_tools/sim_object_param_struct_hh.py:235
 */

#ifndef __PARAMS__X86ACPIMadtIntSourceOverride__
#define __PARAMS__X86ACPIMadtIntSourceOverride__

namespace gem5 {
namespace X86ISA {
namespace ACPI {
namespace MADT {
class IntSourceOverride;
} // namespace MADT
} // namespace ACPI
} // namespace X86ISA
} // namespace gem5
#include <cstddef>
#include "base/types.hh"
#include <cstddef>
#include "base/types.hh"
#include <cstddef>
#include "base/types.hh"
#include <cstddef>
#include "base/types.hh"

#include "params/X86ACPIMadtRecord.hh"

namespace gem5
{
struct X86ACPIMadtIntSourceOverrideParams
    : public X86ACPIMadtRecordParams
{
    gem5::X86ISA::ACPI::MADT::IntSourceOverride * create() const;
    uint8_t bus_source;
    uint16_t flags;
    uint8_t irq_source;
    uint32_t sys_int;
};

} // namespace gem5

#endif // __PARAMS__X86ACPIMadtIntSourceOverride__
