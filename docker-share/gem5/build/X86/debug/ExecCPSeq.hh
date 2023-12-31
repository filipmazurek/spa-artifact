/**
 * DO NOT EDIT THIS FILE!
 * File automatically generated by
 *   build_tools/debugflaghh.py:140
 */

#ifndef __DEBUG_ExecCPSeq_HH__
#define __DEBUG_ExecCPSeq_HH__

#include "base/compiler.hh" // For namespace deprecation
#include "base/debug.hh"
namespace gem5
{

GEM5_DEPRECATED_NAMESPACE(Debug, debug);
namespace debug
{

namespace unions
{
inline union ExecCPSeq
{
    ~ExecCPSeq() {}
    SimpleFlag ExecCPSeq = {
        "ExecCPSeq", "Format: Instruction sequence number", false
    };
} ExecCPSeq;
} // namespace unions

inline constexpr const auto& ExecCPSeq =
    ::gem5::debug::unions::ExecCPSeq.ExecCPSeq;

} // namespace debug
} // namespace gem5

#endif // __DEBUG_ExecCPSeq_HH__
