/**
 * DO NOT EDIT THIS FILE!
 * File automatically generated by
 *   build_tools/sim_object_param_struct_hh.py:235
 */

#ifndef __PARAMS__StridePrefetcher__
#define __PARAMS__StridePrefetcher__

namespace gem5 {
namespace prefetch {
class Stride;
} // namespace prefetch
} // namespace gem5
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
#include "params/BaseIndexingPolicy.hh"
#include <cstddef>
#include "params/BaseReplacementPolicy.hh"
#include <cstddef>

#include "params/QueuedPrefetcher.hh"

namespace gem5
{
struct StridePrefetcherParams
    : public QueuedPrefetcherParams
{
    gem5::prefetch::Stride * create() const;
    unsigned confidence_counter_bits;
    int confidence_threshold;
    int degree;
    unsigned initial_confidence;
    int table_assoc;
    uint64_t table_entries;
    gem5::BaseIndexingPolicy * table_indexing_policy;
    gem5::replacement_policy::Base * table_replacement_policy;
    bool use_requestor_id;
};

} // namespace gem5

#endif // __PARAMS__StridePrefetcher__
