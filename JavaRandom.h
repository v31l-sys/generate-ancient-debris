#pragma once
#include <stdint.h>
#include <math.h>

//literally just a copy past implementation of the Java Random class
class JavaRandom {
    #define get_random(seed) ((uint64_t)((seed ^ 0x5DEECE66DULL) & ((1ULL << 48) - 1)))

    public:
        //new Random()
        JavaRandom();

        //new Random(seed)
        JavaRandom(const int64_t worldSeed);

        //gets state of random
        int64_t getState();

        //sets state of random by seed
        void setState(const int64_t worldSeed);

        //Random::nextLong()
        int64_t next_long();

        // Random::nextFloat()
        float_t next_float();

        //Random::nextInt(bits)
        int32_t next_int(const int32_t bound_size);

        //Random::next(bits)
        int32_t random_next(const int32_t bits);

    protected:
        int64_t seedState;
};
