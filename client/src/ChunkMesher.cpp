#include <client/ChunkMesher.hpp>

#include <client/WorldRenderer.hpp>

#include <bitset>
#include <queue>
#include <spdlog/spdlog.h>

#include <glm/gtx/string_cast.hpp>

#include <client/BlockMeshAlgo.hpp>

namespace hc::client {

thread_local std::queue<ChunkMesher::LightEntry> ChunkMesher::m_light_queue;

template <typename T, typename = std::enable_if_t<std::is_integral_v<T> && std::is_signed_v<T>>>
static inline constexpr uint32_t chunk_xyz_extended15_to_index(T x, T y, T z) {
	bool x_inside = 0 <= x && x < kChunkSize, y_inside = 0 <= y && y < kChunkSize, z_inside = 0 <= z && z < kChunkSize;
	uint32_t bits = x_inside | (y_inside << 1u) | (z_inside << 2u);
	if (bits == 7u)
		return ChunkXYZ2Index(x, y, z);
	constexpr uint32_t kOffsets[8] = {
	    kChunkSize * kChunkSize * kChunkSize,
	    kChunkSize * kChunkSize * kChunkSize + 30 * 30 * 30,
	    kChunkSize * kChunkSize * kChunkSize + 30 * 30 * 30 + 30 * kChunkSize * 30,
	    kChunkSize * kChunkSize * kChunkSize + 30 * 30 * 30 + 30 * kChunkSize * 30 * 2,
	    kChunkSize * kChunkSize * kChunkSize + 30 * 30 * 30 + 30 * kChunkSize * 30 * 2 + kChunkSize * kChunkSize * 30,
	    kChunkSize * kChunkSize * kChunkSize + 30 * 30 * 30 + 30 * kChunkSize * 30 * 3 + kChunkSize * kChunkSize * 30,
	    kChunkSize * kChunkSize * kChunkSize + 30 * 30 * 30 + 30 * kChunkSize * 30 * 3 +
	        kChunkSize * kChunkSize * 30 * 2,
	    0};
	constexpr uint32_t kMultipliers[8][3] = {{30, 30, 30},
	                                         {kChunkSize, 30, 30},
	                                         {30, kChunkSize, 30},
	                                         {kChunkSize, kChunkSize, 30},
	                                         {30, 30, kChunkSize},
	                                         {kChunkSize, 30, kChunkSize},
	                                         {30, kChunkSize, kChunkSize},
	                                         {kChunkSize, kChunkSize, kChunkSize}};
	if (!x_inside)
		x = x < 0 ? x + 15 : x - (int32_t)kChunkSize + 15;
	if (!y_inside)
		y = y < 0 ? y + 15 : y - (int32_t)kChunkSize + 15;
	if (!z_inside)
		z = z < 0 ? z + 15 : z - (int32_t)kChunkSize + 15;
	return kOffsets[bits] + kMultipliers[bits][0] * (kMultipliers[bits][2] * y + z) + x;
}

template <typename T, typename = std::enable_if_t<std::is_integral_v<T> && std::is_signed_v<T>>>
static inline constexpr bool light_interfere(T x, T y, T z, block::LightLvl lvl) {
	if (lvl <= 1)
		return false;
	uint32_t dist = 0;
	if (x < 0 || x >= kChunkSize)
		dist += x < 0 ? -x : x - (int32_t)kChunkSize;
	if (y < 0 || y >= kChunkSize)
		dist += y < 0 ? -y : y - (int32_t)kChunkSize;
	if (z < 0 || z >= kChunkSize)
		dist += z < 0 ? -z : z - (int32_t)kChunkSize;
	return (uint32_t)lvl >= dist;
}

template <typename T, typename = std::enable_if_t<std::is_integral_v<T> && std::is_signed_v<T>>>
static inline constexpr bool chunk_xyz_extended15_in_bound(T x, T y, T z) {
	return !(x < -15 || x >= (int32_t)kChunkSize + 15 || y < -15 || y >= (int32_t)kChunkSize + 15 || z < -15 ||
	         z >= (int32_t)kChunkSize + 15);
}

void ChunkMesher::initial_sunlight_bfs() {
	while (!m_light_queue.empty()) {
		LightEntry e = m_light_queue.front();
		m_light_queue.pop();
		if (e.light_lvl <= 1u)
			continue;
		--e.light_lvl;
		for (block::BlockFace f = 0; f < 6; ++f) {
			LightEntry nei = e;
			block::BlockFaceProceed(glm::value_ptr(nei.position), f);

			if (!chunk_xyz_extended15_in_bound(nei.position.x, nei.position.y, nei.position.z))
				continue;

			uint32_t idx = chunk_xyz_extended15_to_index(nei.position.x, nei.position.y, nei.position.z);
			if (nei.light_lvl > m_light_buffer[idx].GetSunlight() &&
			    get_block(nei.position.x, nei.position.y, nei.position.z).GetIndirectLightPass()) {
				m_light_buffer[idx].SetSunlight(nei.light_lvl);
				if (light_interfere(nei.position.x, nei.position.y, nei.position.z, nei.light_lvl)) {
					m_light_queue.push(nei);
				}
			}
		}
	}
}

void ChunkMesher::Run() {
	if (!lock())
		return;

	// if the neighbour chunks are not totally generated, return and move it back
	for (const auto &i : m_neighbour_chunk_ptr)
		if (!i->IsGenerated()) {
			try_push_worker(ChunkMesher::TryCreateWithInitialLight(m_chunk_ptr));
			return;
		}

	if (m_init_light) {
		// TODO: optimize this
		for (int8_t y = -15; y < (int8_t)kChunkSize + 15; ++y)
			for (int8_t z = -15; z < (int8_t)kChunkSize + 15; ++z)
				for (int8_t x = -15; x < (int8_t)kChunkSize + 15; ++x) {
					block::Light light = get_light(x, y, z);
					m_light_buffer[chunk_xyz_extended15_to_index(x, y, z)] = light;
					if (light_interfere(x, y, z, light.GetSunlight()))
						m_light_queue.push({{x, y, z}, light.GetSunlight()});
					// if (light_interfere(x, y, z, light.GetTorchlight()))
					//	torchlight_queue.Push({{x, y, z}, light.GetTorchlight()});
				}
		initial_sunlight_bfs();
		m_chunk_ptr->PushLight(m_light_version, m_light_buffer);
	}

	std::vector<BlockMesh> meshes =
	    BlockMeshAlgo<BlockAlgoConfig<uint32_t, BlockAlgoBound<uint32_t>{0, 0, 0, kChunkSize, kChunkSize, kChunkSize},
	                                  kBlockAlgoSwizzleYZX>>{}
	        .Generate(
	            [this](auto x, auto y, auto z) -> block::Block { return get_block(x, y, z); },
	            [](auto x, auto y, auto z) -> block::Light { return m_light_buffer[chunk_xyz_extended15_to_index(x, y, z)]; });

	auto world_ptr = m_chunk_ptr->LockWorld();
	if (!world_ptr)
		return;
	std::shared_ptr<WorldRenderer> world_renderer_ptr = world_ptr->LockWorldRenderer();
	if (!world_renderer_ptr)
		return;

	m_chunk_ptr->SetMeshedFlag();

	glm::i32vec3 base_position = (glm::i32vec3)m_chunk_ptr->GetPosition() * (int32_t)Chunk::kSize;
	// erase previous meshes
	std::vector<std::unique_ptr<ChunkMeshHandle>> mesh_handles(meshes.size());
	// spdlog::info("Chunk {} (version {}) meshed with {} meshes", glm::to_string(m_chunk_ptr->GetPosition()),
	// version,meshes.size());
	for (uint32_t i = 0; i < meshes.size(); ++i) {
		auto &info = meshes[i];
		mesh_handles[i] = ChunkMeshHandle::Create(
		    world_renderer_ptr->GetChunkMeshPool(), info.vertices, info.indices,
		    {(fAABB)info.aabb / glm::vec3(1u << BlockVertex::kUnitBitOffset) + (glm::vec3)base_position, base_position,
		     (uint32_t)info.transparent});
	}

	// Push mesh to chunk
	m_chunk_ptr->PushMesh(m_version, mesh_handles);
}

} // namespace hc::client