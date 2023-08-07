#include "global_variable_cache/global_variable_cache.hh"

#include <iostream>

int given_seed_value;

namespace gem5
{

GlobalVariableCache::GlobalVariableCache(const GlobalVariableCacheParams &params) :
    SimObject(params),
    inputSeed(params.inputSeed)
{
    // given_seed_value = params.givenSeed;
    // std::cout << "HENLO" << std::endl;
    std::cout << "instantiated global cache with seed " << inputSeed << std::endl;
    given_seed_value = inputSeed;

}

} // namespace gem5


