#pragma once
#include "public/Trait.hpp"

template <> struct BlockTrait<Blocks::kVine> : public SingleBlockTrait<Blocks::kVine> {
	constexpr static BlockProperty kProperty = {
	    "Vine",
	    BLOCK_TEXTURE_NONE,
	    BlockTransparencies::kTransparent,
	    BlockCollisionBits::kNone,
	};

	inline constexpr static uint8_t kTransforms = 6;
	template <BlockMeta Transform> inline static constexpr BlockProperty TransformProperty(BlockProperty property) {
		property.custom_mesh = BlockMeshes::kInnerSurface<BlockTextures::kVine, Transform, 1>;
		return property;
	}
};
