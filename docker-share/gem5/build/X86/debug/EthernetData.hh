/**
 * DO NOT EDIT THIS FILE!
 * File automatically generated by
 *   build_tools/debugflaghh.py:140
 */

#ifndef __DEBUG_EthernetData_HH__
#define __DEBUG_EthernetData_HH__

#include "base/compiler.hh" // For namespace deprecation
#include "base/debug.hh"
namespace gem5
{

GEM5_DEPRECATED_NAMESPACE(Debug, debug);
namespace debug
{

namespace unions
{
inline union EthernetData
{
    ~EthernetData() {}
    SimpleFlag EthernetData = {
        "EthernetData", "", false
    };
} EthernetData;
} // namespace unions

inline constexpr const auto& EthernetData =
    ::gem5::debug::unions::EthernetData.EthernetData;

} // namespace debug
} // namespace gem5

#endif // __DEBUG_EthernetData_HH__