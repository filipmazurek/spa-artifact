/**
 * DO NOT EDIT THIS FILE!
 * File automatically generated by
 *   build_tools/debugflaghh.py:140
 */

#ifndef __DEBUG_Kvm_HH__
#define __DEBUG_Kvm_HH__

#include "base/compiler.hh" // For namespace deprecation
#include "base/debug.hh"
namespace gem5
{

GEM5_DEPRECATED_NAMESPACE(Debug, debug);
namespace debug
{

namespace unions
{
inline union Kvm
{
    ~Kvm() {}
    SimpleFlag Kvm = {
        "Kvm", "Basic KVM Functionality", false
    };
} Kvm;
} // namespace unions

inline constexpr const auto& Kvm =
    ::gem5::debug::unions::Kvm.Kvm;

} // namespace debug
} // namespace gem5

#endif // __DEBUG_Kvm_HH__
