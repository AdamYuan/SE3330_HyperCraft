#pragma once

#include "../include/resource/block/BlockProperty.hpp"
enum : std::size_t {
#include "../register/blocks"
};
#define BLOCK_TEXTURE_SAME(x) \
	{ x, x, x, x, x, x }
#define BLOCK_TEXTURE_BOT_SIDE_TOP(b, s, t) \
	{ s, s, t, b, s, s }

template <std::size_t> struct BlockTrait;
