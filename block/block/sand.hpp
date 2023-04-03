#pragma once
#include "public/Trait.hpp"

template <> struct BlockTrait<Blocks::kSand> : public SingleBlockTrait<Blocks::kSand> {
	constexpr static BlockProperty kProperty = {
	    "Sand",
	    BLOCK_TEXTURE_SAME(BlockTextures::kSand),
	    BlockTransparencies::kOpaque,
	    BlockCollisionBits::kSolid,
	};
};
