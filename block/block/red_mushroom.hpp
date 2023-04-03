#pragma once
#include "public/Trait.hpp"

template <> struct BlockTrait<kRedMushroom> : public SingleBlockTrait<kRedMushroom> {
	constexpr static BlockProperty kProperty = {
	    "Red Mushroom",
	    BLOCK_TEXTURE_NONE,
	    BlockTransparencies::kTransparent,
	    BlockCollisionBits::kNone,
	    &BlockMeshes::kCross<BlockTextures::kRedMushroom, 5, 0, 12, true>,
	};
};
