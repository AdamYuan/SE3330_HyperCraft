#pragma once
#include "public/Trait.hpp"

template <> struct BlockTrait<Blocks::kDeadBush> : public SingleBlockTrait<Blocks::kDeadBush> {
	constexpr static BlockProperty kProperty = {
	    "Dead Bush",
	    {},
	    BlockTransparencies::kTransparent,
	    BlockCollisionBits::kNone,
	    BlockMeshes::Cross(BlockTextures::kDeadBush, 8, 0, 16),
	};
};
