#pragma once

#include <texture/BlockTexture.hpp>

#include "BlockFace.hpp"
#include "BlockMesh.hpp"

using BlockTransparency = uint8_t;
struct BlockTransparencies {
	enum : uint8_t { kOpaque = 0, kSemiTransparent, kTransparent };
};
using BlockCollisionMask = uint8_t;
struct BlockCollisionBits {
	enum : uint8_t { kNone = 1 << 0, kSolid = 1 << 1, kLiquid = 1 << 2 };
};
struct BlockProperty {
	const char *name{"Unnamed"};
	BlockTexture textures[6]{};
	BlockTransparency transparency{BlockTransparencies::kOpaque};
	BlockCollisionMask collision_mask{BlockCollisionBits::kSolid};
	BlockMesh custom_mesh;

	inline constexpr BlockProperty RotateCW(uint8_t axis) const {
		if (axis == 0) {
			return {name,
			        {
			            textures[0].RotateCW(),
			            textures[1].RotateCCW(),
			            textures[BlockFaces::kFront],
			            textures[BlockFaces::kBack],
			            textures[BlockFaces::kBottom],
			            textures[BlockFaces::kTop],
			        },
			        transparency,
			        collision_mask,
			        custom_mesh};
		} else if (axis == 1) {
			return {name,
			        {
			            textures[BlockFaces::kBack],
			            textures[BlockFaces::kFront],
			            textures[2].RotateCW(),
			            textures[3].RotateCCW(),
			            textures[BlockFaces::kRight],
			            textures[BlockFaces::kLeft],
			        },
			        transparency,
			        collision_mask,
			        custom_mesh};
		} else {
			return {name,
			        {
			            textures[BlockFaces::kTop],
			            textures[BlockFaces::kBottom],
			            textures[BlockFaces::kLeft].TransSwapUV(),
			            textures[BlockFaces::kRight].TransSwapUV(),
			            textures[4].RotateCW(),
			            textures[5].RotateCCW(),
			        },
			        transparency,
			        collision_mask,
			        custom_mesh};
		}
	}
};