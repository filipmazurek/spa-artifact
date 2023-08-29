/**
 * DO NOT EDIT THIS FILE!
 * File automatically generated by
 *   build_tools/sim_object_param_struct_hh.py:235
 */

#ifndef __PARAMS__SectorTags__
#define __PARAMS__SectorTags__

namespace gem5 {
class SectorTags;
} // namespace gem5
#include <cstddef>
#include "base/types.hh"
#include <cstddef>
#include "base/types.hh"
#include <cstddef>
#include "params/BaseReplacementPolicy.hh"

#include "params/BaseTags.hh"

namespace gem5
{
struct SectorTagsParams
    : public BaseTagsParams
{
    gem5::SectorTags * create() const;
    int assoc;
    int num_blocks_per_sector;
    gem5::replacement_policy::Base * replacement_policy;
};

} // namespace gem5

#endif // __PARAMS__SectorTags__
