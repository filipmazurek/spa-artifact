/**
 * DO NOT EDIT THIS FILE!
 * File automatically generated by
 *   build_tools/debugflaghh.py:140
 */

#ifndef __DEBUG_DRAMState_HH__
#define __DEBUG_DRAMState_HH__

#include "base/compiler.hh" // For namespace deprecation
#include "base/debug.hh"
namespace gem5
{

GEM5_DEPRECATED_NAMESPACE(Debug, debug);
namespace debug
{

namespace unions
{
inline union DRAMState
{
    ~DRAMState() {}
    SimpleFlag DRAMState = {
        "DRAMState", "", false
    };
} DRAMState;
} // namespace unions

inline constexpr const auto& DRAMState =
    ::gem5::debug::unions::DRAMState.DRAMState;

} // namespace debug
} // namespace gem5

#endif // __DEBUG_DRAMState_HH__