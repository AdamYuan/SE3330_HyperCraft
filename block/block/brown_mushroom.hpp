#pragma once
#include "public/Trait.hpp"

template <> struct BlockTrait<Blocks::kBrownMushroom> : public SingleBlockTrait<Blocks::kBrownMushroom> {
	constexpr static BlockProperty kProperty = {
	    "Brow Mushroom",
	    BLOCK_TEXTURE_NONE,
	    BlockTransparencies::kTransparent,
	    BlockCollisionBits::kNone,
	    &BlockMeshes::kCross<BlockTextures::kBrownMushroom, 6, 0, 9, true>,
	};
};
