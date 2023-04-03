#pragma once
#include "public/Trait.hpp"

template <> struct BlockTrait<Blocks::kWater> : public SingleBlockTrait<Blocks::kWater> {
	constexpr static BlockProperty kProperty = {
	    "Water",
	    BLOCK_TEXTURE_SAME(BlockTextures::kWater),
	    BlockTransparencies::kSemiTransparent,
	    BlockCollisionBits::kLiquid,
	};
};
