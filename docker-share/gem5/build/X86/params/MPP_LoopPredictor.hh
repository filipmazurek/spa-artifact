/**
 * DO NOT EDIT THIS FILE!
 * File automatically generated by
 *   build_tools/sim_object_param_struct_hh.py:235
 */

#ifndef __PARAMS__MPP_LoopPredictor__
#define __PARAMS__MPP_LoopPredictor__

namespace gem5 {
namespace branch_prediction {
class MPP_LoopPredictor;
} // namespace branch_prediction
} // namespace gem5

#include "params/LoopPredictor.hh"

namespace gem5
{
struct MPP_LoopPredictorParams
    : public LoopPredictorParams
{
    gem5::branch_prediction::MPP_LoopPredictor * create() const;
};

} // namespace gem5

#endif // __PARAMS__MPP_LoopPredictor__
