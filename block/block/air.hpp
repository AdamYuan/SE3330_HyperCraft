#pragma once
#include "public/Trait.hpp"

template <> struct BlockTrait<Blocks::kAir> : public SingleBlockTrait<Blocks::kAir> {
	constexpr static BlockProperty kProperty = {"Air", BLOCK_TEXTURE_NONE, BlockTransparencies::kTransparent,
	                                            BlockCollisionBits::kNone};
};
