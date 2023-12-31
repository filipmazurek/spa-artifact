/**
 * DO NOT EDIT THIS FILE!
 * File automatically generated by
 *   build_tools/debugflaghh.py:140
 */

#ifndef __DEBUG_HtmMem_HH__
#define __DEBUG_HtmMem_HH__

#include "base/compiler.hh" // For namespace deprecation
#include "base/debug.hh"
namespace gem5
{

GEM5_DEPRECATED_NAMESPACE(Debug, debug);
namespace debug
{

namespace unions
{
inline union HtmMem
{
    ~HtmMem() {}
    SimpleFlag HtmMem = {
        "HtmMem", "Hardware Transactional Memory (Mem side)", false
    };
} HtmMem;
} // namespace unions

inline constexpr const auto& HtmMem =
    ::gem5::debug::unions::HtmMem.HtmMem;

} // namespace debug
} // namespace gem5

#endif // __DEBUG_HtmMem_HH__
