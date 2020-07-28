#include <algorithm>
#include "AncientDebrisUtils.h"
using namespace BlockUtils;
using std::vector;

namespace AncientDebrisUtils {
    //Get initial coords for NoSurfaceOre
    BlockPos AncientDebris::get_initial_coords(JavaRandom* random, const BlockPos chunkCoords) {
        //chunk coords y depend on coord alg, calculated before generate step
        int32_t initX = random->next_int(16) + chunkCoords.x;
        int32_t initZ = random->next_int(16) + chunkCoords.z;
        return BlockPos{ initX, chunkCoords.y, initZ };
    }

    //DepthAverageDecorator::getPositions (step 1)
    BlockPos AncientDebris::random_get_initial_large_debris_y(JavaRandom* random, const BlockPos chunkPos) {
        int32_t y = random->next_int(8) + random->next_int(8) + 8; //DepthDecorator count = 16, baseline = 8
        return BlockPos{ chunkPos.x, y, chunkPos.z };
    }

    //RangeDecorator::getPositions (step 2)
    BlockPos AncientDebris::random_get_initial_small_debris_y(JavaRandom* random, const BlockPos chunkPos) {
        int32_t y = random->next_int(112) + 8; //from code, RangeDecorator... bottomOffset = 8, topOffset = 16, maximum = 128
        return BlockPos{ chunkPos.x, y, chunkPos.z };
    }

    //NoSurfaceOreFeature::randomCoord()
    int32_t AncientDebris::get_random_coord(JavaRandom* random, const int32_t oreIteration) {
        return (int32_t)roundf((random->next_float() - random->next_float()) * oreIteration);
    }

    //NoSurfaceOreFeature::getStartPos()
    BlockPos AncientDebris::get_next_pos(JavaRandom* random, const BlockPos blockPos, const int32_t oreIteration) {
        int32_t initX = get_random_coord(random, oreIteration);
        int32_t initY = get_random_coord(random, oreIteration);
        int32_t initZ = get_random_coord(random, oreIteration);
        return BlockPos{ blockPos.x + initX, blockPos.y + initY, blockPos.z + initZ };
    }

    //DepthFeatureConfig - etc
    //random->nextInt(size + 1), size is 3 [0..3] ores to spawn
    vector <BlockPos> AncientDebris::generate_large_debris_locations(ChunkRandom* random, const int64_t populationSeed, const BlockPos chunkCoords, const int16_t biomeIndex) {
        //GET LARGE DEBRIS LOCATION
        return generate_next_debris_locations(random, populationSeed, chunkCoords, biomeIndex, DebrisSpawnType::large);
    }

    //RangeFeatureConfig - etc
    //random->nextInt(size + 1), size is 2 [0..2] ores to spawn
    vector<BlockPos> AncientDebris::generate_small_debris_locations(ChunkRandom* random, const int64_t populationSeed, const BlockPos chunkCoords, const int16_t biomeIndex) {
        //GET SMALL DEBRIS LOCATION
        return generate_next_debris_locations(random, populationSeed, chunkCoords, biomeIndex + 1, DebrisSpawnType::small);
    }

    //Get next Debris location, promotes code reuse
    vector<BlockPos> AncientDebris::generate_next_debris_locations(ChunkRandom* random, const int64_t populationSeed, const BlockPos chunkCoords, const int16_t biomeIndex, const DebrisSpawnType type) {
        vector<BlockPos> positions = vector<BlockPos>();
        random->set_decorator_seed(populationSeed, biomeIndex, 7);
        BlockPos location = BlockPos{ chunkCoords.x, 0, chunkCoords.z };
        location = AncientDebris::get_initial_coords(random, location);

        if (type == DebrisSpawnType::large)
            location = AncientDebris::random_get_initial_large_debris_y(random, location);
        else
            location = AncientDebris::random_get_initial_small_debris_y(random, location);

        int16_t oresToSpawn = random->next_int((int8_t)type);
        BlockPos mutablePos{ };
        for (int i = 0; i < oresToSpawn; i++) {
            mutablePos = get_next_pos(random, location, i);
            //(usually would check if the block is in the air or already occupied, but we're not generating the terrain to check)
            positions.push_back(mutablePos);
        }

        std::sort(positions.begin(), positions.end(), sortByBlockPos);
        positions.erase(std::unique(positions.begin(), positions.end()), positions.end()); //erase duplicates....

        return positions;
    }

    //NoSurfaceOreFeature::generate()
    void AncientDebris::generate_ancient_debris_locations(const int64_t worldSeed, const BlockPos blockPos, const int16_t biomeIndex) {
        //CALCULATES AND SETS CHUNK COORDS:
        const BlockPos chunkCoords = get_chunk_section_coord_from_blockpos(blockPos);
        //JAVA RANDOM INSTANCE
        ChunkRandom* rand = new ChunkRandom;
        //CALCULATE POPULATION SEED USING WORLDSEED, CHUNKX AND CHUNKZ
        int64_t populationSeed = rand->set_population_seed(worldSeed, chunkCoords.x, chunkCoords.z);

        //NOTE, RULES FOR SPAWNING ANCIENT DEBRIS:
        //MUST BE SURROUNDED BY BLOCKS (NO AIR)
        //STATE OF BLOCK MUST BE NETHER DEFAULT (i.e. NOT OVERWRITTEN BY ANOTHER BLOCK)
        //LARGE GENERATES ANYWHERE FROM 0-3, SMALL GENERATES BETWEEN 0-2

        vector<BlockPos> positions = vector<BlockPos>();

        //GET LARGE DEBRIS LOCATION
        positions = generate_large_debris_locations(rand, populationSeed, chunkCoords, biomeIndex);
        if (positions.size() > 0) {
            std::cout << "POTENTIAL LOCATIONS OF LARGE DEBRIS: " << '\n';
            for (uint16_t i = 0; i < positions.size(); i++) {
                std::cout << positions.at(i) << '\n';
            }
        }
        else {
            std::cout << "NO LARGE DEBRIS GENERATED..." << '\n';
        }

        //quick formatting for next locations
        std::cout << '\n';

        //GET SMALL DEBRIS LOCATION
        positions = generate_small_debris_locations(rand, populationSeed, chunkCoords, biomeIndex);
        if (positions.size() > 0) {
            std::cout << "POTENTIAL LOCATIONS OF SMALL DEBRIS: " << '\n';
            for (uint16_t i = 0; i < positions.size(); i++) {
                std::cout << positions.at(i) << '\n';
            }
        }
        else {
            std::cout << "NO SMALL DEBRIS GENERATED..." << '\n';
        }
    }
}
