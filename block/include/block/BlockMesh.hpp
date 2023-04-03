#pragma once

#include "BlockFace.hpp"
#include <AABB.hpp>
#include <texture/BlockTexture.hpp>

#include <cinttypes>
#include <limits>
#include <type_traits>

struct BlockMeshVertex {
	union {
		struct {
			uint8_t x{}, y{}, z{};
		};
		uint8_t pos[3];
	};
	uint8_t ao{4}; // 4 means auto AO
	constexpr BlockMeshVertex() {}
	template <typename T, typename = std::enable_if_t<std::is_integral_v<T>>>
	constexpr BlockMeshVertex(T x, T y, T z, T ao = 4) : x(x), y(y), z(z), ao(ao) {}
};
struct BlockMeshFace {
	uint8_t axis;
	BlockFace light_face{}, render_face{};
	BlockTexture texture{};
	BlockMeshVertex vertices[4]{};
};
#define BLOCK_MESH_MAX_FACE_COUNT 32
constexpr uint32_t kBlockMeshMaxAABBCount = 4;
struct BlockMesh {
	// "faces" array's BlockFace property should be sorted for better performance
	BlockMeshFace faces[BLOCK_MESH_MAX_FACE_COUNT];
	uint32_t face_count{};
	u8AABB aabbs[kBlockMeshMaxAABBCount];
	uint32_t aabb_count{};
};
#undef BLOCK_MESH_MAX_FACE_COUNT

// predefined block meshes
namespace BlockMeshes {
inline static constexpr BlockMesh kCactusSides = {{
                                                      {0,
                                                       BlockFaces::kRight,
                                                       BlockFaces::kRight,
                                                       {BlockTextures::kCactusSide},
                                                       {
                                                           {15, 0, 16},
                                                           {15, 0, 0},
                                                           {15, 16, 0},
                                                           {15, 16, 16},
                                                       }},
                                                      {0,
                                                       BlockFaces::kLeft,
                                                       BlockFaces::kLeft,
                                                       {BlockTextures::kCactusSide},
                                                       {
                                                           {1, 0, 0},
                                                           {1, 0, 16},
                                                           {1, 16, 16},
                                                           {1, 16, 0},
                                                       }},
                                                      {2,
                                                       BlockFaces::kFront,
                                                       BlockFaces::kFront,
                                                       {BlockTextures::kCactusSide},
                                                       {
                                                           {0, 0, 15},
                                                           {16, 0, 15},
                                                           {16, 16, 15},
                                                           {0, 16, 15},
                                                       }},
                                                      {2,
                                                       BlockFaces::kBack,
                                                       BlockFaces::kBack,
                                                       {BlockTextures::kCactusSide},
                                                       {
                                                           {16, 0, 1},
                                                           {0, 0, 1},
                                                           {0, 16, 1},
                                                           {16, 16, 1},
                                                       }},
                                                  },
                                                  4,
                                                  {{{1, 0, 1}, {15, 16, 15}}},
                                                  1};

template <BlockTexID TexID, int Radius, int Low, int High, BlockFace LightFace = BlockFaces::kTop>
inline static constexpr BlockMesh kCross = {{
                                                {0,
                                                 LightFace,
                                                 BlockFaces::kLeft,
                                                 {TexID},
                                                 {
                                                     {8 - Radius, Low, 8 - Radius},
                                                     {8 + Radius, Low, 8 + Radius},
                                                     {8 + Radius, High, 8 + Radius},
                                                     {8 - Radius, High, 8 - Radius},
                                                 }},
                                                {2,
                                                 LightFace,
                                                 BlockFaces::kBack,
                                                 {TexID, BlockTextures::kTransNegU},
                                                 {
                                                     {8 - Radius, Low, 8 + Radius},
                                                     {8 + Radius, Low, 8 - Radius},
                                                     {8 + Radius, High, 8 - Radius},
                                                     {8 - Radius, High, 8 + Radius},
                                                 }},
                                                {0,
                                                 LightFace,
                                                 BlockFaces::kRight,
                                                 {TexID},
                                                 {
                                                     {8 - Radius, High, 8 - Radius},
                                                     {8 + Radius, High, 8 + Radius},
                                                     {8 + Radius, Low, 8 + Radius},
                                                     {8 - Radius, Low, 8 - Radius},
                                                 }},
                                                {2,
                                                 LightFace,
                                                 BlockFaces::kFront,
                                                 {TexID, BlockTextures::kTransNegU},
                                                 {
                                                     {8 - Radius, High, 8 + Radius},
                                                     {8 + Radius, High, 8 - Radius},
                                                     {8 + Radius, Low, 8 - Radius},
                                                     {8 - Radius, Low, 8 + Radius},
                                                 }},
                                            },
                                            BlockTexture{TexID}.UseTransparentPass() ? 2u : 4u,
                                            {{{8 - Radius, Low, 8 - Radius}, {8 + Radius, High, 8 + Radius}}},
                                            1};

inline static constexpr BlockMesh InnerSurface(BlockTexID tex_id, BlockFace face, uint8_t dist) {
	uint8_t axis = face >> 1, u = (axis + 1) % 3, v = (axis + 2) % 3;
	uint8_t du[3] = {0}, dv[3] = {0}, x[3] = {0};
	if (face & 1u) {
		du[v] = dv[u] = 16;
		x[axis] = 16 - (int32_t)dist;
	} else {
		dv[v] = du[u] = 16;
		x[axis] = dist;
	}

	return {{
	            {axis,
	             face,
	             face,
	             {tex_id},
	             {
	                 {x[0], x[1], x[2]},
	                 {x[0] + du[0], x[1] + du[1], x[2] + du[2]},
	                 {x[0] + du[0] + dv[0], x[1] + du[1] + dv[1], x[2] + du[2] + dv[2]},
	                 {x[0] + dv[0], x[1] + dv[1], x[2] + dv[2]},
	             }},
	            {axis,
	             face,
	             (BlockFace)(face ^ 1u),
	             {tex_id},
	             {
	                 {x[0], x[1], x[2]},
	                 {x[0] + dv[0], x[1] + dv[1], x[2] + dv[2]},
	                 {x[0] + du[0] + dv[0], x[1] + du[1] + dv[1], x[2] + du[2] + dv[2]},
	                 {x[0] + du[0], x[1] + du[1], x[2] + du[2]},
	             }},
	        },
	        BlockTexture{tex_id}.UseTransparentPass() ? 1u : 2u,
	        {{{x[0], x[1], x[2]}, {x[0] + du[0] + dv[0], x[1] + du[1] + dv[1], x[2] + du[2] + dv[2]}}},
	        1u};
}

template <BlockTexID TexID, BlockFace Face, uint8_t Dist>
inline static constexpr BlockMesh kInnerSurface = InnerSurface(TexID, Face, Dist);

}; // namespace BlockMeshes
