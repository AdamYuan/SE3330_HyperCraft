#pragma once
#include "public/Trait.hpp"

template <> struct BlockTrait<kCactus> {
	constexpr static BlockProperty kProperty = {
	    "Cactus",
	    BLOCK_TEXTURE_BOT_SIDE_TOP(BlockTextures::kCactusBottom, 0, BlockTextures::kCactusTop),
	    BlockTransparencies::kSemiTransparent,
	    BlockCollisionBits::kSolid,
	    BlockMeshes::CactusSides(),
	};
};
