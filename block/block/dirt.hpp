#pragma once
#include "public/Trait.hpp"

template <> struct BlockTrait<Blocks::kDirt> : public SingleBlockTrait<Blocks::kDirt> {
	constexpr static BlockProperty kProperty = {
	    "Dirt",
	    BLOCK_TEXTURE_SAME(BlockTextures::kDirt),
	    BlockTransparencies::kOpaque,
	    BlockCollisionBits::kSolid,
	};
};
