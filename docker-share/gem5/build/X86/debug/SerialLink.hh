/**
 * DO NOT EDIT THIS FILE!
 * File automatically generated by
 *   build_tools/debugflaghh.py:140
 */

#ifndef __DEBUG_SerialLink_HH__
#define __DEBUG_SerialLink_HH__

#include "base/compiler.hh" // For namespace deprecation
#include "base/debug.hh"
namespace gem5
{

GEM5_DEPRECATED_NAMESPACE(Debug, debug);
namespace debug
{

namespace unions
{
inline union SerialLink
{
    ~SerialLink() {}
    SimpleFlag SerialLink = {
        "SerialLink", "", false
    };
} SerialLink;
} // namespace unions

inline constexpr const auto& SerialLink =
    ::gem5::debug::unions::SerialLink.SerialLink;

} // namespace debug
} // namespace gem5

#endif // __DEBUG_SerialLink_HH__
