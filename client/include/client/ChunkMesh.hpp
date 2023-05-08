#ifndef HYPERCRAFT_COMMON_CHUNK_MESH_HPP
#define HYPERCRAFT_COMMON_CHUNK_MESH_HPP

#include <AABB.hpp>
#include <block/Block.hpp>
#include <common/Light.hpp>

#include "BlockVertex.hpp"
#include "mesh/MeshHandle.hpp"
#include "mesh/MeshPool.hpp"

struct ChunkMeshInfo {
	fAABB aabb;
	glm::i32vec3 base_position;
	uint32_t transparent;
};
static_assert(sizeof(ChunkMeshInfo) == 40);

using ChunkMeshHandle = MeshHandle<BlockVertex, uint16_t, ChunkMeshInfo>;
using ChunkMeshCluster = MeshCluster<BlockVertex, uint16_t, ChunkMeshInfo>;
using ChunkMeshPoolBase = MeshPool<BlockVertex, uint16_t, ChunkMeshInfo>;
using ChunkMeshInfoBuffer = MeshInfoBuffer<BlockVertex, uint16_t, ChunkMeshInfo>;

class ChunkMeshPool : public ChunkMeshPoolBase {
private:
	inline static constexpr uint32_t kClusterFaceCount = 4 * 1024 * 1024;
	inline static constexpr uint32_t kMaxMeshesPerCluster = 4096u, kMaxClusters = 8u;

public:
	explicit ChunkMeshPool(const myvk::Ptr<myvk::Device> &device)
	    : ChunkMeshPoolBase(device, kClusterFaceCount * 4 * sizeof(BlockVertex),
	                        kClusterFaceCount * 6 * sizeof(uint16_t), kMaxClusters, kMaxMeshesPerCluster) {}

	inline static std::shared_ptr<ChunkMeshPool> Create(const myvk::Ptr<myvk::Device> &device) {
		return std::make_shared<ChunkMeshPool>(device);
	}
};

#endif
