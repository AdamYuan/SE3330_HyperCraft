#pragma once
#include "public/Trait.hpp"

template <> struct BlockTrait<kCobblestone> {
	constexpr static BlockProperty kProperty = {
	    "Cobblestone",
	    BLOCK_TEXTURE_SAME(BlockTextures::kCobblestone),
	    BlockTransparencies::kOpaque,
	    BlockCollisionBits::kSolid,
	};
};
