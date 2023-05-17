#pragma once

#include <block/Light.hpp>
#include <glm/glm.hpp>
#include <queue>

#include "BlockAlgo.hpp"

namespace hc::client {

template <typename Config> class BlockLightAlgo {
private:
	struct LightEntry {
		glm::i8vec3 position;
		block::LightLvl light_lvl;
	};
	std::queue<LightEntry> m_queue;
};

} // namespace hc::client