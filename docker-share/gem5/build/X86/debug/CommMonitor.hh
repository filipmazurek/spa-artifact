/**
 * DO NOT EDIT THIS FILE!
 * File automatically generated by
 *   build_tools/debugflaghh.py:140
 */

#ifndef __DEBUG_CommMonitor_HH__
#define __DEBUG_CommMonitor_HH__

#include "base/compiler.hh" // For namespace deprecation
#include "base/debug.hh"
namespace gem5
{

GEM5_DEPRECATED_NAMESPACE(Debug, debug);
namespace debug
{

namespace unions
{
inline union CommMonitor
{
    ~CommMonitor() {}
    SimpleFlag CommMonitor = {
        "CommMonitor", "", false
    };
} CommMonitor;
} // namespace unions

inline constexpr const auto& CommMonitor =
    ::gem5::debug::unions::CommMonitor.CommMonitor;

} // namespace debug
} // namespace gem5

#endif // __DEBUG_CommMonitor_HH__
