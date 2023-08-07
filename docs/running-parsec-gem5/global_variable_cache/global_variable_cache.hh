#ifndef __GLOBAL_VARIABLE_CACHE_HH__
#define __GLOBAL_VARIABLE_CACHE_HH__

#include "params/GlobalVariableCache.hh"
#include "sim/sim_object.hh"

extern int given_seed_value;

namespace gem5
{

class GlobalVariableCache : public SimObject
{
  public:
    GlobalVariableCache(const GlobalVariableCacheParams &p);
    int inputSeed;
};

} // namespace gem5

#endif // __GLOBAL_VARIABLE_CACHE_HH__