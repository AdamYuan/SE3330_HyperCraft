#pragma once
#include "public/Trait.hpp"

template <> struct BlockTrait<Blocks::kIce> : public SingleBlockTrait<Blocks::kIce> {
	constexpr static BlockProperty kProperty = {
	    "Ice",
	    BLOCK_TEXTURE_SAME(BlockTextures::kIce),
	    BlockTransparencies::kSemiTransparent,
	    BlockCollisionBits::kSolid,
	};
};
