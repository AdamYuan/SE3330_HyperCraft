#pragma once
#include "public/Trait.hpp"

template <> struct BlockTrait<Blocks::kBlueIce> : public SingleBlockTrait<Blocks::kBlueIce> {
	constexpr static BlockProperty kProperty = {"Blue Ice", BLOCK_TEXTURE_SAME(BlockTextures::kBlueIce),
	                                            BlockTransparencies::kOpaque, BlockCollisionBits::kSolid};
};
