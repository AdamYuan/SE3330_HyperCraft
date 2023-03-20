#ifndef HYPERCRAFT_COMMON_BIOME_HPP
#define HYPERCRAFT_COMMON_BIOME_HPP

#include <cinttypes>

using Biome = uint8_t;
struct Biomes {
	enum : Biome {
		kOcean = 0,
		kPlain,
		kSavanna, kTundra,
		kGlacier,
		kDesert,
		kForest,
		kTropicalForest,
		kBorealForest
	};
};

#endif
