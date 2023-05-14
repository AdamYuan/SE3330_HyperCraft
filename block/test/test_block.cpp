#include "catch_amalgamated.hpp"

#include <block/Block.hpp>
#include <limits>

using namespace hc::block;

TEST_CASE("BlockID = 0 is Air", "[block::Block]") {
	for (BlockMeta variant = 0; variant < std::numeric_limits<BlockMeta>::max(); ++variant)
		for (BlockMeta transform = 0; transform < std::numeric_limits<BlockMeta>::max(); ++transform) {
			REQUIRE(Block(0, variant, transform).GetName() != nullptr);

			REQUIRE(Block(0, variant, transform).GetName() == std::string{"Air"});
			REQUIRE(Block(0, variant, transform).GetCollisionMask() == BlockCollisionBits::kNone);
			REQUIRE(Block(0, variant, transform).GetIndirectLightPass() == true);
			REQUIRE(Block(0, variant, transform).GetVerticalLightPass() == true);
			REQUIRE(Block(0, variant, transform).GetCustomMesh() == nullptr);
		}
}

TEST_CASE("Custom Meshes", "[block::Block]") {
	for (BlockID id = 0; id < std::numeric_limits<BlockID>::max(); ++id)
		for (BlockMeta variant = 0; variant < std::numeric_limits<BlockMeta>::max(); ++variant)
			for (BlockMeta transform = 0; transform < std::numeric_limits<BlockMeta>::max(); ++transform) {
				Block block{id, variant, transform};
				if (block.HaveCustomMesh()) {
					REQUIRE(block.GetCustomMesh() != nullptr);

					REQUIRE(block.GetCustomMesh()->face_count != 0);
					REQUIRE(block.GetCustomMesh()->face_count <= kBlockMeshMaxFaceCount);

					REQUIRE(block.GetCustomMesh()->aabb_count <= kBlockMeshMaxAABBCount);

					for (uint32_t f = 0; f < block.GetCustomMesh()->face_count; ++f) {
						const auto &face = block.GetCustomMesh()->faces[f];
						REQUIRE(!face.texture.Empty());                // Custom Mesh Faces should not be empty
						REQUIRE(face.axis == (face.render_face >> 1)); // Axis must match Render Face
					}
				} else
					REQUIRE(block.GetCustomMesh() == nullptr);
			}
}

TEST_CASE("Block Name != nullptr", "[block::Block]") {
	for (BlockID id = 0; id < std::numeric_limits<BlockID>::max(); ++id)
		for (BlockMeta variant = 0; variant < std::numeric_limits<BlockMeta>::max(); ++variant)
			for (BlockMeta transform = 0; transform < std::numeric_limits<BlockMeta>::max(); ++transform) {
				REQUIRE(Block(id, variant, transform).GetName() != nullptr);
			}
}

TEST_CASE("Block Lighting", "[block::Block]") {
	for (BlockID id = 0; id < std::numeric_limits<BlockID>::max(); ++id)
		for (BlockMeta variant = 0; variant < std::numeric_limits<BlockMeta>::max(); ++variant)
			for (BlockMeta transform = 0; transform < std::numeric_limits<BlockMeta>::max(); ++transform) {
				Block block{id, variant, transform};
				if (block.GetVerticalLightPass())
					REQUIRE(block.GetIndirectLightPass());
			}
}
