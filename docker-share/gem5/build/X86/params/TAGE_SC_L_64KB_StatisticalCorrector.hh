/**
 * DO NOT EDIT THIS FILE!
 * File automatically generated by
 *   build_tools/sim_object_param_struct_hh.py:235
 */

#ifndef __PARAMS__TAGE_SC_L_64KB_StatisticalCorrector__
#define __PARAMS__TAGE_SC_L_64KB_StatisticalCorrector__

namespace gem5 {
namespace branch_prediction {
class TAGE_SC_L_64KB_StatisticalCorrector;
} // namespace branch_prediction
} // namespace gem5
#include <vector>
#include "base/types.hh"
#include <cstddef>
#include "base/types.hh"
#include <cstddef>
#include "base/types.hh"
#include <cstddef>
#include "base/types.hh"
#include <cstddef>
#include "base/types.hh"
#include <cstddef>
#include "base/types.hh"
#include <cstddef>
#include "base/types.hh"
#include <cstddef>
#include "base/types.hh"
#include <vector>
#include "base/types.hh"
#include <cstddef>
#include "base/types.hh"
#include <vector>
#include "base/types.hh"
#include <cstddef>
#include "base/types.hh"
#include <vector>
#include "base/types.hh"
#include <cstddef>
#include "base/types.hh"

#include "params/StatisticalCorrector.hh"

namespace gem5
{
struct TAGE_SC_L_64KB_StatisticalCorrectorParams
    : public StatisticalCorrectorParams
{
    gem5::branch_prediction::TAGE_SC_L_64KB_StatisticalCorrector * create() const;
    std::vector< int > imm;
    unsigned imnb;
    unsigned logImnb;
    unsigned logPnb;
    unsigned logSnb;
    unsigned logTnb;
    unsigned numEntriesSecondLocalHistories;
    unsigned numEntriesThirdLocalHistories;
    std::vector< int > pm;
    unsigned pnb;
    std::vector< int > sm;
    unsigned snb;
    std::vector< int > tm;
    unsigned tnb;
};

} // namespace gem5

#endif // __PARAMS__TAGE_SC_L_64KB_StatisticalCorrector__
