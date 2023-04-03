#pragma once
#include "public/Trait.hpp"

template <> struct BlockTrait<Blocks::kGravel> : public SingleBlockTrait<Blocks::kGravel> {
	constexpr static BlockProperty kProperty = {
	    "Gravel",
	    BLOCK_TEXTURE_SAME(BlockTextures::kGravel),
	    BlockTransparencies::kOpaque,
	    BlockCollisionBits::kSolid,
	};
};
