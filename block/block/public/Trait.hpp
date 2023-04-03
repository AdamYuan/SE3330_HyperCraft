#pragma once

#include "../../include/block/BlockProperty.hpp"
#include <texture/BlockTexture.hpp>

using BlockID = uint8_t;
using BlockMeta = uint8_t;

namespace Blocks {
enum : BlockID {
#include "../../register/blocks"
};
} // namespace Blocks

#define BLOCK_TEXTURE_SAME(x) \
	{ x, x, x, x, x, x }
#define BLOCK_TEXTURE_BOT_SIDE_TOP(b, s, t) \
	{ s, s, t, b, s, s }

template <BlockID> struct BlockTrait {
	inline static constexpr uint32_t kVariantBits = 0;
	inline static constexpr uint32_t kTransformBits = 0;
	inline static constexpr BlockProperty GetProperty(uint8_t variant, uint8_t transform) { return {}; }
};

template <BlockID ID> struct SingleBlockTrait {
	inline static constexpr uint32_t kVariantBits = 0;
	inline static constexpr uint32_t kTransformBits = 0;
	inline static constexpr BlockProperty GetProperty(uint8_t variant, uint8_t transform) {
		return BlockTrait<ID>::kProperty;
	}
};