/**
 * DO NOT EDIT THIS FILE!
 * File automatically generated by
 *   build_tools/debugflaghh.py:140
 */

#ifndef __DEBUG_MemCheckerMonitor_HH__
#define __DEBUG_MemCheckerMonitor_HH__

#include "base/compiler.hh" // For namespace deprecation
#include "base/debug.hh"
namespace gem5
{

GEM5_DEPRECATED_NAMESPACE(Debug, debug);
namespace debug
{

namespace unions
{
inline union MemCheckerMonitor
{
    ~MemCheckerMonitor() {}
    SimpleFlag MemCheckerMonitor = {
        "MemCheckerMonitor", "", false
    };
} MemCheckerMonitor;
} // namespace unions

inline constexpr const auto& MemCheckerMonitor =
    ::gem5::debug::unions::MemCheckerMonitor.MemCheckerMonitor;

} // namespace debug
} // namespace gem5

#endif // __DEBUG_MemCheckerMonitor_HH__
