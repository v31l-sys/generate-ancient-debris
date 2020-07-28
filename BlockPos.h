#pragma once
#include <iostream>
#include <stdint.h>

namespace BlockUtils {
    struct BlockPos {
        int32_t x;
        int32_t y;
        int32_t z;
    };

    //Calculates base chunk coordinates
    BlockPos get_chunk_section_coord_from_blockpos(const BlockPos blockPos);

    bool operator==(const BlockPos& lhs, const BlockPos& rhs);

    std::ostream& operator<<(std::ostream& os, const BlockPos& blck);

    bool sortByBlockPos(const BlockPos& lhs, const BlockPos& rhs);
}
