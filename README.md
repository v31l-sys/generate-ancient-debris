# generate-ancient-debris
All the math required to generate the locations of ancient debris.

Modes: USER_INPUT 0, USER_INPUT 1

If USER_INPUT is 0 then this indicates manual data entry.<br>
If USER_INPUT is 1 (default) this indicates interactive data entry.

Usage explained in code, NULL values and correct BiomeFeatureIndexOffset must be set by user if USER_INPUT 0:

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
Expected outputs at end of program in interactive:

>Enter World Seed: 5305720880811071213
>
>BLOCK POSITION X: -1321<br>
>BLOCK POSITION Z: -854
>
>WHICH BIOME IS AT THIS X,Z? OPTIONS:<br>
>0: soul_sand_valley<br>
>1: crimson_forest<br>
>2: warped_forest<br>
>3: nether_wastes<br>
>4: basalt_delta
>
>CHOOSE AN OPTION: 3
>
>POTENTIAL LOCATIONS OF LARGE DEBRIS:<br>
>{ X: -1322, Y: 15, Z: -855 }<br>
>{ X: -1322, Y: 16, Z: -854 }<br>
>{ X: -1321, Y: 17, Z: -854 }
>
>POTENTIAL LOCATIONS OF SMALL DEBRIS:<br>
>{ X: -1322, Y: 101, Z: -850 }
>
>Continue? (Y/n): y<br>
>Same World Seed? (Y/n): y

Tells you the potential locations of large and small ancient debris.
