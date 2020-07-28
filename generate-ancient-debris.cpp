#include <iostream>
#include "AncientDebrisUtils.h"
#include <algorithm>
#include <tuple>
using namespace BlockUtils;

#define USER_INPUT 1

int main()
{
    using std::cout;
    using std::cin;

    //IF YOU WISH TO USE MANUAL INPUT FOR SOME REASON SET the #define USER_INPUT TO 0
    //SET THESE VALUES//////////////////////////////////////////////////////SET THESE VALUES
    //YOUR WORLD SEED GOES HERE: (notation: 238218947LL) add LL to the end of the number.
    int64_t worldSeed = NULL;
    //WHAT IS THE POSITION OF THE BLOCK YOU'RE LOOKING AT? X,Y,Z, ASSUMPTIONS: X, Y, Z ARE BOUNDED BY 32 bits.
    //NOTE: Y VALUE DOES NOT MATTER SINCE THIS IS CALCULATING A CHUNK SECTION COORDINATE AND NOT A CHUNK COORDINATE
    BlockPos blockToUse = { NULL, NULL, NULL };
    //WHAT BIOME IS YOUR BLOCK IN? THIS EFFECTS GENERATION
    //OPTIONS: nether_wastes, soul_sand_valley, basalt_deltas, warped_forest, crimson_forest
    //EX: int16_t biomeIndex = (int16_t)AncientDebrisUtils::BiomeFeatureIndexOffset::nether_wastes;
    int16_t biomeIndex = NULL;
    ///////////////////////////////////////////////////////////////////////////////////////

    //PREPROCESSOR: IF USER_INPUT IS 1 THEN COORDINATES WILL BE SOLVED WITH USER INPUTS
    if (USER_INPUT == 1) {
        int32_t x, z;
        char loopContinue;
        bool enterWorldSeed = true;

        while (true) {
            try {
                if (enterWorldSeed == true) {
                    cout << "Enter World Seed: ";
                    cin >> worldSeed;
                    if (cin.fail())
                        throw "Invalid World Seed Input...";
                    cout << '\n';
                }

                cout << "BLOCK POSITION X: ";
                cin >> x;
                if (cin.fail())
                    throw "Invalid X Input...";

                cout << "BLOCK POSITION Z: ";
                cin >> z;
                if (cin.fail())
                    throw "Invalid Z Input...";

                do {
                    cout << '\n';
                    cout << "WHICH BIOME IS AT THIS X,Z? OPTIONS:\n"
                        << "0: soul_sand_valley\n"
                        << "1: crimson_forest\n"
                        << "2: warped_forest\n"
                        << "3: nether_wastes\n"
                        << "4: basalt_delta\n\n"
                        << "CHOOSE AN OPTION: ";
                    cin >> biomeIndex;
                    if (cin.fail())
                        throw "Invalid Biome Selection Input...";

                    cout << '\n';
                } while (biomeIndex < 0 || biomeIndex > 4);

                switch (biomeIndex) {
                    case 0:
                        biomeIndex = (int16_t)AncientDebrisUtils::BiomeFeatureIndexOffset::soul_sand_valley;
                        break;
                    case 1:
                        biomeIndex = (int16_t)AncientDebrisUtils::BiomeFeatureIndexOffset::crimson_forest;
                        break;
                    case 2:
                        biomeIndex = (int16_t)AncientDebrisUtils::BiomeFeatureIndexOffset::warped_forest;
                        break;
                    case 3:
                        biomeIndex = (int16_t)AncientDebrisUtils::BiomeFeatureIndexOffset::nether_wastes;
                        break;
                    case 4:
                        biomeIndex = (int16_t)AncientDebrisUtils::BiomeFeatureIndexOffset::basalt_deltas;
                        break;
                }

                AncientDebrisUtils::AncientDebris::generate_ancient_debris_locations(worldSeed, BlockPos{ x, 0, z }, biomeIndex);

                cout << '\n' << "Continue? (Y/n): ";
                cin >> loopContinue;
                if (cin.fail())
                    throw "Invalid Continuation Input...";

                if (toupper(loopContinue) == 'Y') {
                    cout << "Same World Seed? (Y/n): ";
                    cin >> loopContinue;
                    if (cin.fail())
                        throw "Invalid Continuation Input...";

                    if (toupper(loopContinue) == 'Y')
                        enterWorldSeed = false;
                    else
                        enterWorldSeed = true;

                    cout << '\n';
                    continue;
                }
                else
                    break;
            }
            catch (const char* error) {
                cout << error << " Resetting Loop\n\n";

                cin.clear();
                cin.ignore(INT_MAX, '\n');
            }
        }
    }
    else {
        AncientDebrisUtils::AncientDebris::generate_ancient_debris_locations(worldSeed, blockToUse, biomeIndex);
        cin.get();
    }

    return 0;
}
