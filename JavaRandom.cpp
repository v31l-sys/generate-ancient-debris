#include "JavaRandom.h"

//new Random()
JavaRandom::JavaRandom() {
    seedState = 0;
}

//new Random(seed)
JavaRandom::JavaRandom(const int64_t worldSeed) {
    seedState = get_random(worldSeed);
}

//gets state of random
int64_t JavaRandom::getState() {
    return seedState;
}

//sets state of random by seed
void JavaRandom::setState(const int64_t worldSeed) {
    seedState = get_random(worldSeed);
}

//Random::nextLong()
int64_t JavaRandom::next_long() {
    return (static_cast<long long>(random_next(32)) << 32) + random_next(32);
}

// Random::nextFloat()
float_t JavaRandom::next_float() {
    return random_next(24) / ((float_t)(1 << 24));
}

//Random::nextInt(bits)
int32_t JavaRandom::next_int(const int32_t bound_size) {
    if ((bound_size & -bound_size) == bound_size)  // i.e., bound is a power of 2
        return (bound_size * static_cast<long long>(random_next(31))) >> 31;
    else
        return random_next(31) % bound_size;
}

//Random::next(bits)
int32_t JavaRandom::random_next(const int32_t bits) {
    seedState = (seedState * 0x5DEECE66DULL + 0xBULL) & ((1ULL << 48) - 1);
    return (int32_t)(seedState >> (48 - bits));
}
