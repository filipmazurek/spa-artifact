/**
 * DO NOT EDIT THIS FILE!
 * File automatically generated by
 *   build_tools/sim_object_param_struct_hh.py:235
 */

#ifndef __PARAMS__X86NativeTrace__
#define __PARAMS__X86NativeTrace__

namespace gem5 {
namespace trace {
class X86NativeTrace;
} // namespace trace
} // namespace gem5

#include "params/NativeTrace.hh"

namespace gem5
{
struct X86NativeTraceParams
    : public NativeTraceParams
{
    gem5::trace::X86NativeTrace * create() const;
};

} // namespace gem5

#endif // __PARAMS__X86NativeTrace__
