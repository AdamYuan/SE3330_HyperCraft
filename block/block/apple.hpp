#pragma once
#include "public/Trait.hpp"

template <> struct BlockTrait<kApple> {
	constexpr static BlockProperty kProperty = {
	    "Apple",
	    {},
	    BlockTransparencies::kTransparent,
	    BlockCollisionBits::kNone,
	    BlockMeshes::Cross(BlockTextures::kApple, 5, 1, 15, BlockFaces::kBottom)};
};
