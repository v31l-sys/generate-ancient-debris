#include "BlockPos.h"
#include <tuple>

using namespace BlockUtils;

//Calculates base chunk coordinates
BlockPos BlockUtils::get_chunk_section_coord_from_blockpos(const BlockPos blockPos) {
    return BlockPos{ (blockPos.x >> 4) * 16, (blockPos.y >> 4) * 16, (blockPos.z >> 4) * 16 };
}

bool BlockUtils::operator==(const BlockPos& lhs, const BlockPos& rhs) {
    return ((lhs.x == rhs.x) && (lhs.y == rhs.y) && (lhs.z == rhs.z));
}

std::ostream& BlockUtils::operator<<(std::ostream& os, const BlockPos& blck) {
    os << "{ X: " << blck.x << ", Y: " << blck.y << ", Z: " << blck.z << " }";
    return os;
}

bool BlockUtils::sortByBlockPos(const BlockPos& lhs, const BlockPos& rhs) {
    return std::tie(lhs.x, lhs.z) < std::tie(rhs.x, rhs.z);
}
