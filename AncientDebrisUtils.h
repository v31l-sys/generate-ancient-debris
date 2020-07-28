#pragma once
#include <vector>
#include "BlockPos.h"
#include "JavaRandom.h"
#include "ChunkRandom.h"

namespace AncientDebrisUtils {
    using namespace BlockUtils;

    //BiomeFeatureIndexOffset IS THE OFFSET OF THE LARGE ANCIENT DEBRIS FEATURE
    enum class BiomeFeatureIndexOffset : int8_t {
        soul_sand_valley = 15,
        crimson_forest = 12,
        warped_forest = 13,
        nether_wastes = 15,
        basalt_deltas = 15
    };

    enum class DebrisSpawnType : int8_t {
        large = 4,
        small = 3
    };

    class AncientDebris {
    public:
        //Get initial coords for NoSurfaceOre
        static BlockPos get_initial_coords(JavaRandom* random, const BlockPos chunkCoords);

        //DepthAverageDecorator::getPositions (step 1)
        static BlockPos random_get_initial_large_debris_y(JavaRandom* random, const BlockPos chunkPos);

        //RangeDecorator::getPositions (step 2)
        static BlockPos random_get_initial_small_debris_y(JavaRandom* random, const BlockPos chunkPos);

        //NoSurfaceOreFeature::randomCoord()
        static int32_t get_random_coord(JavaRandom* random, const int32_t oreIteration);

        //NoSurfaceOreFeature::getStartPos()
        static BlockPos get_next_pos(JavaRandom* random, const BlockPos blockPos, const int32_t oreIteration);

        //DepthFeatureConfig - etc
        static std::vector<BlockPos> generate_large_debris_locations(ChunkRandom* random, const int64_t populationSeed, const BlockPos chunkCoords, const int16_t biomeIndex);

        //RangeFeatureConfig - etc
        static std::vector<BlockPos> generate_small_debris_locations(ChunkRandom* random, const int64_t populationSeed, const BlockPos chunkCoords, const int16_t biomeIndex);

        //Get next Debris location, promotes code reuse
        static std::vector<BlockPos> generate_next_debris_locations(ChunkRandom* random, const int64_t populationSeed, const BlockPos chunkCoords, const int16_t biomeIndex, const DebrisSpawnType type);

        //NoSurfaceOreFeature::generate()
        static void generate_ancient_debris_locations(const int64_t worldSeed, const BlockPos blockPos, const int16_t biomeIndex);
    };
}
