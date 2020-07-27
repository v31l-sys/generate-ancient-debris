# generate-ancient-debris
All the math required to generate the locations of ancient debris in a single simple cpp file.

Usage explained in code, NULL values and correct BiomeFeatureIndexOffset must be set by user:

```c
//SET THESE VALUES//////////////////////////////////////////////////////SET THESE VALUES
//YOUR WORLD SEED GOES HERE: (notation: 238218947LL) add LL to the end of the number.
const int64_t worldSeed = NULL;
//WHAT IS THE POSITION OF THE BLOCK YOU'RE LOOKING AT? X,Y,Z
const BlockPos blockToUse = { NULL, NULL, NULL };
//WHAT BIOME IS YOUR BLOCK IN? THIS EFFECTS GENERATION
//OPTIONS: nether_wastes, soul_sand_valley, basalt_delta, warped_forest, crimson_forest
int32_t biomeIndex = (int32_t)BiomeFeatureIndexOffset::nether_wastes;
///////////////////////////////////////////////////////////////////////////////////////
```
Expected output:

LARGE ANCIENT DEBRIS LOCATION: { X: 599, Y: 18, Z: -1554 } POSSIBLE GEN: 0  
SMALL ANCIENT DEBRIS LOCATION: { X: 599, Y: 92, Z: -1567 } POSSIBLE GEN: 2

Tells you the locations of large and small ancient debris, and how many potentially generated.
