#pragma once
#include "public/Trait.hpp"

template <> struct BlockTrait<kGrass> : public MultiBlockTrait<kGrass> {
	inline constexpr static BlockProperty kProperties[] = {
	    {
	        "Grass",
	        BLOCK_TEXTURE_NONE,
	        BlockTransparencies::kTransparent,
	        BlockCollisionBits::kNone,
	        &BlockMeshes::kCross<BlockTextures::kGrassPlain, 8, 0, 16>,
	    },
	    {
	        "Grass",
	        BLOCK_TEXTURE_NONE,
	        BlockTransparencies::kTransparent,
	        BlockCollisionBits::kNone,
	        &BlockMeshes::kCross<BlockTextures::kGrassSavanna, 8, 0, 16>,
	    },
	    {
	        "Grass",
	        BLOCK_TEXTURE_NONE,
	        BlockTransparencies::kTransparent,
	        BlockCollisionBits::kNone,
	        &BlockMeshes::kCross<BlockTextures::kGrassTropical, 8, 0, 16>,
	    },
	    {
	        "Grass",
	        BLOCK_TEXTURE_NONE,
	        BlockTransparencies::kTransparent,
	        BlockCollisionBits::kNone,
	        &BlockMeshes::kCross<BlockTextures::kGrassBoreal, 8, 0, 16>,
	    },
	};
};
