#include "ChunkRandom.h"

//ChunkRandom::setPopulationSeed()
int64_t ChunkRandom::set_population_seed(const int64_t worldSeed, const int32_t blockX, const int32_t blockZ) {
    seedState = get_random(worldSeed);
    int64_t s1 = next_long() | 0x1ULL;
    int64_t s2 = next_long() | 0x1ULL;
    int64_t newSeed = blockX * s1 + blockZ * s2 ^ worldSeed;
    seedState = get_random(newSeed);
    return newSeed;
}

//ChunkRandom::setDecoratorSeed()
int64_t ChunkRandom::set_decorator_seed(const int64_t populationSeed, const int16_t index, const int16_t step) {
    int64_t newSeed = populationSeed + index + 10000 * step;
    seedState = get_random(newSeed);
    return newSeed;
}
