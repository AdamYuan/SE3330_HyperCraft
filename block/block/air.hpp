#pragma once
#include "public/Trait.hpp"

template <> struct BlockTrait<Blocks::kAir> : public SingleBlockTrait<Blocks::kAir> {
	constexpr static BlockProperty kProperty = {"Air", BLOCK_TEXTURE_SAME(BlockTextures::kNone),
	                                            BlockTransparencies::kTransparent, BlockCollisionBits::kNone};
};
