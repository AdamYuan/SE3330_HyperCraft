#pragma once
#include "public/Trait.hpp"

template <> struct BlockTrait<Blocks::kSnow> : public SingleBlockTrait<Blocks::kSnow> {
	constexpr static BlockProperty kProperty = {
	    "Snow",
	    BLOCK_TEXTURE_SAME(BlockTextures::kSnow),
	    BlockTransparencies::kOpaque,
	    BlockCollisionBits::kSolid,
	};
};
