#include "catch_amalgamated.hpp"

#include <block/Block.hpp>
#include <limits>

using namespace hc::block;

TEST_CASE("BlockID = 0 is Air", "[hc::block::Block]") {
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

TEST_CASE("Block Custom Meshes", "[hc::block::Block]") {
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

TEST_CASE("Block Name != nullptr", "[hc::block::Block]") {
	for (BlockID id = 0; id < std::numeric_limits<BlockID>::max(); ++id)
		for (BlockMeta variant = 0; variant < std::numeric_limits<BlockMeta>::max(); ++variant)
			for (BlockMeta transform = 0; transform < std::numeric_limits<BlockMeta>::max(); ++transform) {
				REQUIRE(Block(id, variant, transform).GetName() != nullptr);
			}
}

TEST_CASE("Block Lighting", "[hc::block::Block]") {
	for (BlockID id = 0; id < std::numeric_limits<BlockID>::max(); ++id)
		for (BlockMeta variant = 0; variant < std::numeric_limits<BlockMeta>::max(); ++variant)
			for (BlockMeta transform = 0; transform < std::numeric_limits<BlockMeta>::max(); ++transform) {
				Block block{id, variant, transform};
				if (block.GetVerticalLightPass())
					REQUIRE(block.GetIndirectLightPass());
			}
}

TEST_CASE("BlockFaceOpposite()", "[hc::block::BlockFace]") {
	REQUIRE(BlockFaceOpposite(BlockFaces::kRight) == BlockFaces::kLeft);
	REQUIRE(BlockFaceOpposite(BlockFaces::kLeft) == BlockFaces::kRight);

	REQUIRE(BlockFaceOpposite(BlockFaces::kFront) == BlockFaces::kBack);
	REQUIRE(BlockFaceOpposite(BlockFaces::kBack) == BlockFaces::kFront);

	REQUIRE(BlockFaceOpposite(BlockFaces::kTop) == BlockFaces::kBottom);
	REQUIRE(BlockFaceOpposite(BlockFaces::kBottom) == BlockFaces::kTop);
}

TEST_CASE("BlockFaceProceed()", "[hc::block::BlockFace]") {
	REQUIRE(BlockFaceProceed(glm::i32vec3{0, 0, 0}, BlockFaces::kRight) == glm::i32vec3{1, 0, 0});
	REQUIRE(BlockFaceProceed(glm::i32vec3{123120312, 77, 23}, BlockFaces::kLeft) == glm::i32vec3{123120311, 77, 23});
	REQUIRE(BlockFaceProceed(glm::i32vec3{-1231, -77, 23}, BlockFaces::kTop) == glm::i32vec3{-1231, -76, 23});
	REQUIRE(BlockFaceProceed(glm::i32vec3{-123, -7, 2}, BlockFaces::kBottom) == glm::i32vec3{-123, -8, 2});
	REQUIRE(BlockFaceProceed(glm::i32vec3{72334, -3245, 0x23}, BlockFaces::kFront) == glm::i32vec3{72334, -3245, 0x24});
	REQUIRE(BlockFaceProceed(glm::i32vec3{1424, -245, 0x234}, BlockFaces::kBack) == glm::i32vec3{1424, -245, 0x233});
}
