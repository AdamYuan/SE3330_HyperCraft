#pragma once
#include "public/Trait.hpp"

template <> struct BlockTrait<Blocks::kGlass> : public SingleBlockTrait<Blocks::kGlass> {
	constexpr static BlockProperty kProperty = {
	    "Glass",
	    BLOCK_TEXTURE_SAME(BlockTextures::kGlass),
	    BlockTransparencies::kTransparent,
	    BlockCollisionBits::kSolid,
	};
};
