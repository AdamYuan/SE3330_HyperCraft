#pragma once
#include "public/Trait.hpp"

template <> struct BlockTrait<Blocks::kGrass> : public MultiBlockTrait<Blocks::kGrass> {
	inline constexpr static BlockProperty kProperties[] = {
	    {
	        "Grass",
	        BLOCK_TEXTURE_NONE,
	        BlockTransparencies::kTransparent,
	        BlockCollisionBits::kNone,
	        BlockMeshes::Cross(BlockTextures::kGrassPlain, 8, 0, 16),
	    },
	    {
	        "Grass",
	        BLOCK_TEXTURE_NONE,
	        BlockTransparencies::kTransparent,
	        BlockCollisionBits::kNone,
	        BlockMeshes::Cross(BlockTextures::kGrassSavanna, 8, 0, 16),
	    },
	    {
	        "Grass",
	        BLOCK_TEXTURE_NONE,
	        BlockTransparencies::kTransparent,
	        BlockCollisionBits::kNone,
	        BlockMeshes::Cross(BlockTextures::kGrassTropical, 8, 0, 16),
	    },
	    {
	        "Grass",
	        BLOCK_TEXTURE_NONE,
	        BlockTransparencies::kTransparent,
	        BlockCollisionBits::kNone,
	        BlockMeshes::Cross(BlockTextures::kGrassBoreal, 8, 0, 16),
	    },
	};
};
