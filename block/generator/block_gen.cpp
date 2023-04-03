#include <iostream>

#include "../block/air.hpp"
#include "../block/apple.hpp"
#include "../block/blue_ice.hpp"
#include "../block/brown_mushroom.hpp"
#include "../block/cactus.hpp"
#include "../block/cobblestone.hpp"
#include "../block/dead_bush.hpp"
#include "../block/dirt.hpp"
#include "../block/glass.hpp"
#include "../block/grass.hpp"
#include "../block/grass_block.hpp"
#include "../block/gravel.hpp"
#include "../block/ice.hpp"
#include "../block/leaves.hpp"
#include "../block/log.hpp"
#include "../block/plank.hpp"
#include "../block/red_mushroom.hpp"
#include "../block/sand.hpp"
#include "../block/sandstone.hpp"
#include "../block/snow.hpp"
#include "../block/stone.hpp"
#include "../block/vine.hpp"
#include "../block/water.hpp"

using BlockID = uint8_t;
using BlockMeta = uint8_t;

class Block {
private:
	union {
		uint16_t m_data;
		struct {
#ifdef IS_SMALL_ENDIAN
			uint8_t m_id, m_meta; // regular order for little endian
#else
			uint8_t m_meta, m_id;
#endif
		};
	};

	template <uint16_t Data> using BlockDataTrait = BlockTrait<Data & 0xffu>;
	template <uint16_t Data>
	inline static constexpr uint8_t kBlockDataVariant = (Data >> 8u) & ((1u << BlockDataTrait<Data>::kVariantBits) - 1);
	template <uint16_t Data>
	inline static constexpr uint8_t kBlockDataTransform =
	    (Data >> (8u + BlockDataTrait<Data>::kVariantBits)) & ((1u << BlockDataTrait<Data>::kTransformBits) - 1);
	template <uint16_t Data>
	inline static constexpr BlockProperty kBlockDataProperty =
	    BlockDataTrait<Data>::GetProperty(kBlockDataVariant<Data>, kBlockDataTransform<Data>);
	template <typename DataSequence> struct BlockDataTable;
	template <std::size_t... DataArray> struct BlockDataTable<std::index_sequence<DataArray...>> {
		inline static constexpr BlockProperty kProperties[] = {(kBlockDataProperty<DataArray>)...};
	};
	inline static constexpr const BlockProperty *kBlockDataProperties =
	    BlockDataTable<std::make_index_sequence<256>>::kProperties;

	inline static constexpr u8AABB kDefaultAABB{{0, 0, 0}, {16, 16, 16}};

	inline constexpr const BlockProperty *get_property() const { return kBlockDataProperties + m_data; }

public:
	inline constexpr Block() : m_data{} {}
	inline constexpr Block(uint16_t data) : m_data{data} {}
	inline constexpr Block(BlockID id, BlockMeta meta) : m_id{id}, m_meta{meta} {}
	// inline constexpr Block(BlockID id, BlockMeta variant, BlockMeta transform) : m_id{id}, m_meta{meta} {}

	inline constexpr BlockID GetID() const { return m_id; }
	inline void SetID(BlockID id) { m_id = id; }
	inline constexpr BlockMeta GetMeta() const { return m_meta; }
	inline void SetMeta(BlockMeta meta) { m_meta = meta; }

	inline constexpr uint16_t GetData() const { return m_data; }
	inline void SetData(uint16_t data) { m_data = data; }

	inline constexpr bool HaveCustomMesh() const { return get_property()->custom_mesh.face_count; }
	inline constexpr const BlockMesh *GetCustomMesh() const { return &get_property()->custom_mesh; }
	inline constexpr const u8AABB *GetAABBs() const {
		return HaveCustomMesh() ? GetCustomMesh()->aabbs : &kDefaultAABB;
	}
	inline constexpr uint32_t GetAABBCount() const { return HaveCustomMesh() ? GetCustomMesh()->aabb_count : 1; }
	inline constexpr const char *GetName() const { return get_property()->name; }
	inline constexpr BlockTexture GetTexture(BlockFace face) const { return get_property()->textures[face]; }
	// Vertical Sunlight
	inline constexpr BlockTransparency GetTransparency() const { return get_property()->transparency; }
	inline constexpr bool GetVerticalLightPass() const {
		return GetTransparency() == BlockTransparencies::kTransparent;
	}
	inline constexpr bool GetIndirectLightPass() const { return GetTransparency() != BlockTransparencies::kOpaque; }

	inline constexpr BlockCollisionMask GetCollisionMask() const { return get_property()->collision_mask; }

	inline constexpr bool ShowFace(BlockFace face, Block neighbour) const {
		BlockTexture tex = GetTexture(face), nei_tex = neighbour.GetTexture(BlockFaceOpposite(face));
		if (tex.Empty() || tex == nei_tex)
			return false;
		if (!tex.IsTransparent() && !nei_tex.IsTransparent())
			return false;
		if (tex.IsLiquid() && !nei_tex.Empty())
			return false;
		return !tex.IsTransparent() || nei_tex.IsTransparent() || nei_tex.IsLiquid();
	}

	bool operator==(Block r) const { return m_data == r.m_data; }
	bool operator!=(Block r) const { return m_data != r.m_data; }
};

int main() { printf("%d\n", Block(Blocks::kStone).GetTransparency()); }