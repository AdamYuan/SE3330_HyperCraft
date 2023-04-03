#pragma once
#include "public/Trait.hpp"

template <> struct BlockTrait<Blocks::kGrass> {
	inline constexpr static BlockProperty kProperties[] = {
	    {"Grass",
	     {},
	     BlockTransparencies::kTransparent,
	     BlockCollisionBits::kNone,
	     BlockMeshes::Cross(BlockTextures::kGrassPlain, 8, 0, 16)},
	    {"Grass",
	     {},
	     BlockTransparencies::kTransparent,
	     BlockCollisionBits::kNone,
	     BlockMeshes::Cross(BlockTextures::kGrassSavanna, 8, 0, 16)},
	    {"Grass",
	     {},
	     BlockTransparencies::kTransparent,
	     BlockCollisionBits::kNone,
	     BlockMeshes::Cross(BlockTextures::kGrassTropical, 8, 0, 16)},
	    {"Grass",
	     {},
	     BlockTransparencies::kTransparent,
	     BlockCollisionBits::kNone,
	     BlockMeshes::Cross(BlockTextures::kGrassBoreal, 8, 0, 16)},
	};
	inline static constexpr BlockProperty GetProperty(uint8_t variant, uint8_t transform) {
		return kProperties[variant];
	}
};
