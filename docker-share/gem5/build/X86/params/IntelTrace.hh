/**
 * DO NOT EDIT THIS FILE!
 * File automatically generated by
 *   build_tools/sim_object_param_struct_hh.py:235
 */

#ifndef __PARAMS__IntelTrace__
#define __PARAMS__IntelTrace__

namespace gem5 {
namespace trace {
class IntelTrace;
} // namespace trace
} // namespace gem5

#include "params/InstTracer.hh"

namespace gem5
{
struct IntelTraceParams
    : public InstTracerParams
{
    gem5::trace::IntelTrace * create() const;
};

} // namespace gem5

#endif // __PARAMS__IntelTrace__
