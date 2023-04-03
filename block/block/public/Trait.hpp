#pragma once

#include "../../include/block/BlockProperty.hpp"
#include <bit>
#include <texture/BlockTexture.hpp>

using BlockID = uint8_t;
using BlockMeta = uint8_t;

namespace Blocks {
enum : BlockID {
#include "../../register/blocks"
};
} // namespace Blocks

#define BLOCK_TEXTURE_NONE \
	{ \
		{}, {}, {}, {}, {}, {} \
	}
#define BLOCK_TEXTURE_SAME(x) \
	{ x, x, x, x, x, x }
#define BLOCK_TEXTURE_BOT_SIDE_TOP(b, s, t) \
	{ s, s, t, b, s, s }

template <BlockID> struct BlockTrait {
	inline static constexpr uint32_t kVariantBits = 0;
	inline static constexpr uint32_t kTransformBits = 0;
	inline static constexpr BlockProperty GetProperty(BlockMeta variant, BlockMeta transform) {
		return {"None", BLOCK_TEXTURE_NONE, BlockTransparencies::kTransparent, BlockCollisionBits::kNone};
	}
};

template <BlockID ID> struct SingleBlockTrait {
	inline static constexpr uint32_t kVariantBits = 0;
	inline static constexpr uint32_t kTransformBits = 0;
	inline static constexpr BlockProperty TransformProperty(BlockProperty property, BlockMeta transform) {
		return property;
	}
	inline static constexpr BlockProperty GetProperty(BlockMeta variant, BlockMeta transform) {
		return BlockTrait<ID>::TransformProperty(BlockTrait<ID>::kProperty, transform);
	}
};

template <BlockID ID> struct MultiBlockTrait {
	inline static constexpr uint32_t kVariantBits =
	    std::countr_zero(std::bit_ceil(sizeof(BlockTrait<ID>::kProperties) / sizeof(BlockProperty)));
	inline static constexpr uint32_t kTransformBits = 0;
	inline static constexpr BlockProperty TransformProperty(BlockProperty property, BlockMeta transform) {
		return property;
	}
	inline static constexpr BlockProperty GetProperty(BlockMeta variant, BlockMeta transform) {
		return BlockTrait<ID>::TransformProperty(BlockTrait<ID>::kProperties[variant], transform);
	}
};
