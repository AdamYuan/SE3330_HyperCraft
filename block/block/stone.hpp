#pragma once
#include "public/Trait.hpp"

template <> struct BlockTrait<Blocks::kStone> : public SingleBlockTrait<Blocks::kStone> {
	constexpr static BlockProperty kProperty = {"Stone", BLOCK_TEXTURE_SAME(BlockTextures::kStone),
	                                            BlockTransparencies::kOpaque, BlockCollisionBits::kSolid};
};
