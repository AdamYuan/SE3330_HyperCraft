#pragma once
#include "public/Trait.hpp"

template <> struct BlockTrait<kAir> {
	constexpr static BlockProperty kProperty = {"Air", BLOCK_TEXTURE_SAME(BlockTextures::kNone),
	                                            BlockTransparencies::kTransparent, BlockCollisionBits::kNone};
};
