/**
 * DO NOT EDIT THIS FILE!
 * File automatically generated by
 *   build_tools/debugflaghh.py:140
 */

#ifndef __DEBUG_PciDevice_HH__
#define __DEBUG_PciDevice_HH__

#include "base/compiler.hh" // For namespace deprecation
#include "base/debug.hh"
namespace gem5
{

GEM5_DEPRECATED_NAMESPACE(Debug, debug);
namespace debug
{

namespace unions
{
inline union PciDevice
{
    ~PciDevice() {}
    SimpleFlag PciDevice = {
        "PciDevice", "", false
    };
} PciDevice;
} // namespace unions

inline constexpr const auto& PciDevice =
    ::gem5::debug::unions::PciDevice.PciDevice;

} // namespace debug
} // namespace gem5

#endif // __DEBUG_PciDevice_HH__