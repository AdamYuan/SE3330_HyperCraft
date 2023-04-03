#pragma once
#include "public/Trait.hpp"

template <> struct BlockTrait<Blocks::kRedMushroom> : public SingleBlockTrait<Blocks::kRedMushroom> {
	constexpr static BlockProperty kProperty = {
	    "Red Mushroom",
	    BLOCK_TEXTURE_NONE,
	    BlockTransparencies::kTransparent,
	    BlockCollisionBits::kNone,
	    &BlockMeshes::kCross<BlockTextures::kRedMushroom, 5, 0, 12, true>,
	};
};
