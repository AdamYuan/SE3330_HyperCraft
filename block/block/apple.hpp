#pragma once
#include "public/Trait.hpp"

template <> struct BlockTrait<Blocks::kApple> : public SingleBlockTrait<Blocks::kApple> {
	constexpr static BlockProperty kProperty = {
	    "Apple",
	    BLOCK_TEXTURE_NONE,
	    BlockTransparencies::kTransparent,
	    BlockCollisionBits::kNone,
	    BlockMeshes::kCross<BlockTextures::kApple, 5, 1, 15, BlockFaces::kBottom>,
	};
};
