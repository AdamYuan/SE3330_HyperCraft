#pragma once
#include "public/Trait.hpp"

template <> struct BlockTrait<Blocks::kDeadBush> : public SingleBlockTrait<Blocks::kDeadBush> {
	constexpr static BlockProperty kProperty = {
	    "Dead Bush",
	    BLOCK_TEXTURE_NONE,
	    BlockTransparencies::kTransparent,
	    BlockCollisionBits::kNone,
	    &BlockMeshes::kCross<BlockTextures::kDeadBush, 8, 0, 16>,
	};
};
