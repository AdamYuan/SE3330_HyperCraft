#ifndef HYPERCRAFT_CLIENT_CHUNK_LIGHTER_HPP
#define HYPERCRAFT_CLIENT_CHUNK_LIGHTER_HPP

#include <client/ChunkWorkerBase.hpp>
#include <common/Light.hpp>

class ChunkLighter : public ChunkWorkerS26Base {
private:
	bool m_initial_pass{false};
	std::vector<glm::ivec3> m_mods;

public:
	static inline std::unique_ptr<ChunkLighter> TryCreateInitial(const std::shared_ptr<Chunk> &chunk_ptr) {
		if (chunk_ptr->GetLightSync().IsPending())
			return nullptr;
		chunk_ptr->GetLightSync().Pend();
		return std::make_unique<ChunkLighter>(chunk_ptr);
	}
	static inline std::unique_ptr<ChunkLighter> TryCreate(const std::shared_ptr<Chunk> &chunk_ptr, bool initial_pass,
	                                                      std::vector<glm::ivec3> &&mods) {
		if (chunk_ptr->GetLightSync().IsPending())
			return nullptr;
		chunk_ptr->GetLightSync().Pend();
		return std::make_unique<ChunkLighter>(chunk_ptr, initial_pass, std::move(mods));
	}

	explicit ChunkLighter(const std::shared_ptr<Chunk> &chunk_ptr)
	    : ChunkWorkerS26Base(chunk_ptr), m_initial_pass{true} {}
	explicit ChunkLighter(const std::shared_ptr<Chunk> &chunk_ptr, std::vector<glm::ivec3> &&mods)
	    : ChunkWorkerS26Base(chunk_ptr), m_initial_pass{false}, m_mods(std::move(mods)) {}
	explicit ChunkLighter(const std::shared_ptr<Chunk> &chunk_ptr, bool initial_pass, std::vector<glm::ivec3> &&mods)
	    : ChunkWorkerS26Base(chunk_ptr), m_initial_pass{initial_pass}, m_mods(std::move(mods)) {}
	~ChunkLighter() override = default;
	void Run() override;
};

#endif
