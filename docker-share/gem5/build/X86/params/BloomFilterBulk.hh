/**
 * DO NOT EDIT THIS FILE!
 * File automatically generated by
 *   build_tools/sim_object_param_struct_hh.py:235
 */

#ifndef __PARAMS__BloomFilterBulk__
#define __PARAMS__BloomFilterBulk__

namespace gem5 {
namespace bloom_filter {
class Bulk;
} // namespace bloom_filter
} // namespace gem5

#include "params/BloomFilterMultiBitSel.hh"

namespace gem5
{
struct BloomFilterBulkParams
    : public BloomFilterMultiBitSelParams
{
    gem5::bloom_filter::Bulk * create() const;
};

} // namespace gem5

#endif // __PARAMS__BloomFilterBulk__
