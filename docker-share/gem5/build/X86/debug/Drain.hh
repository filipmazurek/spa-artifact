/**
 * DO NOT EDIT THIS FILE!
 * File automatically generated by
 *   build_tools/debugflaghh.py:140
 */

#ifndef __DEBUG_Drain_HH__
#define __DEBUG_Drain_HH__

#include "base/compiler.hh" // For namespace deprecation
#include "base/debug.hh"
namespace gem5
{

GEM5_DEPRECATED_NAMESPACE(Debug, debug);
namespace debug
{

namespace unions
{
inline union Drain
{
    ~Drain() {}
    SimpleFlag Drain = {
        "Drain", "", false
    };
} Drain;
} // namespace unions

inline constexpr const auto& Drain =
    ::gem5::debug::unions::Drain.Drain;

} // namespace debug
} // namespace gem5

#endif // __DEBUG_Drain_HH__