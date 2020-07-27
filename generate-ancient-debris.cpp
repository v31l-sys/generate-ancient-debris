#include <iostream>

//literally just a copy past implementation of the Java Random class
class JavaRandom {
#define get_random(seed) ((uint64_t)((seed ^ 0x5DEECE66DULL) & ((1ULL << 48) - 1)))

public:
    //ChunkRandom::setPopulationSeed()
    int64_t set_population_seed(int64_t worldSeed, int32_t blockX, int32_t blockZ) {
        seedState = get_random(worldSeed);
        int64_t s1 = next_long() | 0x1ULL;
        int64_t s2 = next_long() | 0x1ULL;
        int64_t calc = blockX * s1 + blockZ * s2 ^ worldSeed;
        seedState = get_random(calc);
        return calc;
    }

    //ChunkRandom::setDecoratorSeed()
    int64_t set_decorator_seed(int64_t populationSeed, int16_t index, int16_t step) {
        int64_t calc = populationSeed + index + 10000 * step;
        seedState = get_random(calc);
        return calc;
    }

    //Random::nextLong()
    int64_t next_long() {
        return (static_cast<long long>(random_next(32)) << 32) + random_next(32);
    }

    //Random::nextInt(bits)
    int32_t next_int(int32_t bound_size) {
        if ((bound_size & -bound_size) == bound_size)  // i.e., bound is a power of 2
            return (bound_size * static_cast<long long>(random_next(31))) >> 31;
        else
            return random_next(31) % bound_size;
    }

    //Random::next(bits)
    int32_t random_next(int32_t bits) {
        seedState = (seedState * 0x5DEECE66DULL + 0xBULL) & ((1ULL << 48) - 1);
        return (int32_t)(seedState >> (48 - bits));
    }

private:
    int64_t seedState;
};

struct BlockPos {
    int32_t x;
    int32_t y;
    int32_t z;
};

class AncientDebrisUtils {
public:
    //Calculates base chunk coordinates
    static BlockPos get_chunk_coord_from_blockpos(BlockPos blockPos) {
        return BlockPos{ (blockPos.x >> 4) * 16, (blockPos.y >> 4) * 16, (blockPos.z >> 4) * 16 };
    }

    //Get initial coords for NoSurfaceOre
    static BlockPos get_initial_coords(JavaRandom* random, BlockPos chunkCoords) {
        //chunk coords y depend on coord alg, calculated before generate step
        int32_t initX = random->next_int(16) + chunkCoords.x;
        int32_t initZ = random->next_int(16) + chunkCoords.z;
        return BlockPos{ initX, chunkCoords.y, initZ };
    }

    //DepthAverageDecorator::getPositions (step 1)
    static BlockPos random_get_large_debris_location(JavaRandom* random, BlockPos chunkPos) {
        int32_t y = random->next_int(8) + random->next_int(8) + 8; //DepthDecorator count = 16, baseline = 8
        return BlockPos{ chunkPos.x, y, chunkPos.z };
    }

    //RangeDecorator::getPositions (step 2)
    static BlockPos random_get_small_debris_location(JavaRandom* random, BlockPos chunkPos) {
        int32_t y = random->next_int(112) + 8; //from code, RangeDecorator... bottomOffset = 8, topOffset = 16, maximum = 128
        return BlockPos{ chunkPos.x, y, chunkPos.z };
    }
};

//BiomeFeatureIndexOffset IS THE OFFSET OF THE LARGE ANCIENT DEBRIS FEATURE
enum class BiomeFeatureIndexOffset : int8_t {
    nether_wastes = 15,
    soul_sand_valley = 15,
    basalt_delta = 15,
    warped_forest = 13,
    crimson_forest = 12
};

std::ostream& operator<<(std::ostream& os, const BlockPos& blck) {
    os << "{ X: " << blck.x << ", Y: " << blck.y << ", Z: " << blck.z << " }";
    return os;
}

int main()
{
    //SET THESE VALUES//////////////////////////////////////////////////////SET THESE VALUES
    //YOUR WORLD SEED GOES HERE: (notation: 238218947LL) add LL to the end of the number.
    const int64_t worldSeed = 412343458;
    //WHAT IS THE POSITION OF THE BLOCK YOU'RE LOOKING AT? X,Y,Z
    const BlockPos blockToUse = { 598, 37, -1567 };
    //WHAT BIOME IS YOUR BLOCK IN? THIS EFFECTS GENERATION
    //OPTIONS: nether_wastes, soul_sand_valley, basalt_delta, warped_forest, crimson_forest
    int32_t biomeIndex = (int32_t)BiomeFeatureIndexOffset::soul_sand_valley;
    ///////////////////////////////////////////////////////////////////////////////////////

    //CALCULATES AND SETS CHUNK COORDS:
    const BlockPos chunkCoords = AncientDebrisUtils::get_chunk_coord_from_blockpos(blockToUse);
    //JAVA RANDOM INSTANCE
    JavaRandom* rand = new JavaRandom;
    //CALCULATE POPULATION SEED USING WORLDSEED, CHUNKX AND CHUNKZ
    int64_t populationSeed = rand->set_population_seed(worldSeed, chunkCoords.x, chunkCoords.z);

    //NOTE, RULES FOR SPAWNING ANCIENT DEBRIS:
    //MUST BE SURROUNDED BY BLOCKS (NO AIR)
    //STATE OF BLOCK MUST BE NETHER DEFAULT (i.e. NOT OVERWRITTEN BY ANOTHER BLOCK)
    //LARGE GENERATES ANYWHERE FROM 0-3, SMALL GENERATES BETWEEN 0-2

    //GET LARGE DEBRIS LOCATION
    rand->set_decorator_seed(populationSeed, biomeIndex, 7);
    BlockPos location = BlockPos{ chunkCoords.x, 0, chunkCoords.z };
    location = AncientDebrisUtils::get_initial_coords(rand, location);
    location = AncientDebrisUtils::random_get_large_debris_location(rand, location);
    std::cout << "LARGE ANCIENT DEBRIS LOCATION: " << location << " POSSIBLE GEN: " << rand->next_int(4) << '\n';

    //GET SMALL DEBRIS LOCATION
    rand->set_decorator_seed(populationSeed, biomeIndex + 1, 7);
    location = BlockPos{ chunkCoords.x, 0, chunkCoords.z };
    location = AncientDebrisUtils::get_initial_coords(rand, location);
    location = AncientDebrisUtils::random_get_small_debris_location(rand, location);
    std::cout << "SMALL ANCIENT DEBRIS LOCATION: " << location << " POSSIBLE GEN: " << rand->next_int(3) << '\n';

    std::cin.get();
    return 0;
}
