/**
 * DO NOT EDIT THIS FILE!
 * File automatically generated by
 *   build_tools/debugflaghh.py:140
 */

#ifndef __DEBUG_ProtocolTrace_HH__
#define __DEBUG_ProtocolTrace_HH__

#include "base/compiler.hh" // For namespace deprecation
#include "base/debug.hh"
namespace gem5
{

GEM5_DEPRECATED_NAMESPACE(Debug, debug);
namespace debug
{

namespace unions
{
inline union ProtocolTrace
{
    ~ProtocolTrace() {}
    SimpleFlag ProtocolTrace = {
        "ProtocolTrace", "", false
    };
} ProtocolTrace;
} // namespace unions

inline constexpr const auto& ProtocolTrace =
    ::gem5::debug::unions::ProtocolTrace.ProtocolTrace;

} // namespace debug
} // namespace gem5

#endif // __DEBUG_ProtocolTrace_HH__
