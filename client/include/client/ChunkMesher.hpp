#ifndef HYPERCRAFT_CLIENT_CHUNK_MESHER_HPP
#define HYPERCRAFT_CLIENT_CHUNK_MESHER_HPP

#include <AABB.hpp>
#include <client/ChunkMesh.hpp>
#include <client/ChunkWorkerBase.hpp>
#include <queue>

namespace hc::client {

class ChunkMesher final : public ChunkWorkerS26Base {
public:
	static inline std::unique_ptr<ChunkMesher> TryCreate(const std::shared_ptr<Chunk> &chunk_ptr) {
		if (chunk_ptr->GetMeshSync().IsPending())
			return nullptr;
		chunk_ptr->GetMeshSync().Pend();
		return std::make_unique<ChunkMesher>(chunk_ptr, false);
	}
	static inline std::unique_ptr<ChunkMesher> TryCreateWithInitialLight(const std::shared_ptr<Chunk> &chunk_ptr) {
		if (chunk_ptr->GetMeshSync().IsPending() && chunk_ptr->GetLightSync().IsPending())
			return nullptr;
		chunk_ptr->GetMeshSync().Pend();
		chunk_ptr->GetLightSync().Pend();
		return std::make_unique<ChunkMesher>(chunk_ptr, true);
	}

	explicit ChunkMesher(const std::shared_ptr<Chunk> &chunk_ptr, bool init_light = false)
	    : ChunkWorkerS26Base(chunk_ptr), m_init_light{init_light} {}
	~ChunkMesher() override = default;

	void Run() override;

private:
	inline bool lock() final {
		if (!ChunkWorkerS26Base::lock()) {
			if (m_chunk_ptr) {
				m_chunk_ptr->GetMeshSync().Cancel();
				if (m_init_light)
					m_chunk_ptr->GetLightSync().Cancel();
			}
			return false;
		}
		if (!m_chunk_ptr->IsGenerated()) {
			m_chunk_ptr->GetMeshSync().Cancel();
			if (m_init_light)
				m_chunk_ptr->GetLightSync().Cancel();
			return false;
		}
		m_version = m_chunk_ptr->GetMeshSync().FetchVersion();
		if (m_init_light)
			m_light_version = m_chunk_ptr->GetLightSync().FetchVersion();
		return true;
	}
	bool m_init_light{};
	uint64_t m_version{}, m_light_version{};
	struct LightEntry {
		glm::i8vec3 position;
		LightLvl light_lvl;
	};
	static_assert(sizeof(LightEntry) == 4);
	inline static thread_local Light m_light_buffer[(kChunkSize + 30) * (kChunkSize + 30) * (kChunkSize + 30)]{};
	static thread_local std::queue<LightEntry> m_light_queue;

	struct AO4 { // compressed ambient occlusion data for 4 vertices (a face)
		uint8_t m_data;
		inline uint8_t Get(uint32_t i) const { return (m_data >> (i << 1u)) & 0x3u; }
		inline void Set(uint32_t i, uint8_t ao) {
			uint8_t mask = ~(0x3u << (i << 1u));
			m_data = (m_data & mask) | (ao << (i << 1u));
		}
		inline uint8_t operator[](uint32_t i) const { return Get(i); }
		inline bool operator==(AO4 r) const { return m_data == r.m_data; }
		inline bool operator!=(AO4 r) const { return m_data != r.m_data; }
	};
	struct Light4 { // compressed light data for 4 vertices (a face)
		union {
			struct {
				uint8_t sunlight[4], torchlight[4];
			};
			uint64_t lights;
		};
		AO4 ao;
		inline bool GetFlip() const {
			return std::abs((int32_t)(ao[0] + 1) * (sunlight[0] + 1) - (ao[2] + 1) * (sunlight[2] + 1))
			       // + std::max(m_light[0].GetTorchlight(), m_light[2].GetTorchlight())
			       < std::abs((int32_t)(ao[1] + 1) * (sunlight[1] + 1) - (ao[3] + 1) * (sunlight[3] + 1));
			// + std::max(m_light[1].GetTorchlight(), m_light[3].GetTorchlight());
		}
		inline bool operator==(Light4 f) const { return ao == f.ao && lights == f.lights; }
		inline bool operator!=(Light4 f) const { return ao != f.ao || lights != f.lights; }
	};

	struct MeshGenInfo {
		std::vector<BlockVertex> vertices;
		std::vector<uint16_t> indices;
		AABB<uint32_t> aabb{};
		bool transparent;
	};

	void initial_sunlight_bfs();
	void light4_init(Light4 *light4, block::BlockFace face, int_fast8_t x, int_fast8_t y, int_fast8_t z) const;
	static void light4_interpolate(const Light4 &low_light, const Light4 &high_light, uint8_t du, uint8_t dv,
	                               uint8_t dw, uint8_t *ao, uint8_t *sunlight, uint8_t *torchlight);
	std::vector<MeshGenInfo> generate_mesh() const;
};

} // namespace hc::client

#endif
