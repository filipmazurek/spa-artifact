/**
 * DO NOT EDIT THIS FILE!
 * File automatically generated by
 *   build_tools/sim_object_param_struct_hh.py:235
 */

#ifndef __PARAMS__TimingExprLet__
#define __PARAMS__TimingExprLet__

namespace gem5 {
class TimingExprLet;
} // namespace gem5
#include <vector>
#include "params/TimingExpr.hh"
#include <cstddef>
#include "params/TimingExpr.hh"

#include "params/TimingExpr.hh"

namespace gem5
{
struct TimingExprLetParams
    : public TimingExprParams
{
    gem5::TimingExprLet * create() const;
    std::vector< gem5::TimingExpr * > defns;
    gem5::TimingExpr * expr;
};

} // namespace gem5

#endif // __PARAMS__TimingExprLet__
