#pragma once
#include "public/Trait.hpp"

template <> struct BlockTrait<Blocks::kSandstone> : public SingleBlockTrait<Blocks::kSandstone> {
	constexpr static BlockProperty kProperty = {
		"Sandstone",
		BLOCK_TEXTURE_SAME(BlockTextures::kSandstone),
		BlockTransparencies::kOpaque,
		BlockCollisionBits::kSolid,
	};
};
