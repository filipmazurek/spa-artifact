/**
 * DO NOT EDIT THIS FILE!
 * File automatically generated by
 *   build_tools/debugflaghh.py:140
 */

#ifndef __DEBUG_ExecRegDelta_HH__
#define __DEBUG_ExecRegDelta_HH__

#include "base/compiler.hh" // For namespace deprecation
#include "base/debug.hh"
namespace gem5
{

GEM5_DEPRECATED_NAMESPACE(Debug, debug);
namespace debug
{

namespace unions
{
inline union ExecRegDelta
{
    ~ExecRegDelta() {}
    SimpleFlag ExecRegDelta = {
        "ExecRegDelta", "", false
    };
} ExecRegDelta;
} // namespace unions

inline constexpr const auto& ExecRegDelta =
    ::gem5::debug::unions::ExecRegDelta.ExecRegDelta;

} // namespace debug
} // namespace gem5

#endif // __DEBUG_ExecRegDelta_HH__
