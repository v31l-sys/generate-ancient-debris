#pragma once
#include "JavaRandom.h"

//some functions from Minecraft ChunkRandom
class ChunkRandom : public JavaRandom {
public:
    //ChunkRandom::setPopulationSeed()
    int64_t set_population_seed(const int64_t worldSeed, const int32_t blockX, const int32_t blockZ);

    //ChunkRandom::setDecoratorSeed()
    int64_t set_decorator_seed(const int64_t populationSeed, const int16_t index, const int16_t step);
};
