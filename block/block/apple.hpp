#pragma once
#include "public/Trait.hpp"

template <> struct BlockTrait<kApple> : public SingleBlockTrait<kApple> {
	constexpr static BlockProperty kProperty = {
	    "Apple",
	    BLOCK_TEXTURE_NONE,
	    BlockTransparencies::kTransparent,
	    BlockCollisionBits::kNone,
	    &BlockMeshes::kCross<BlockTextures::kApple, 5, 1, 15, BlockFaces::kBottom>,
	};
};
