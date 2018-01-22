#include "engine/comp/tilemap.hpp"

CompTilemap::CompTilemap() {}

CompTilemap::CompTilemap(EntityId entity_id, TilesetHandle tileset, Vec2 pos,
                         u32 w, u32 h, Vec2 tile_size, u32 *tiles)
    : entity_id(entity_id), tileset(tileset), pos(pos), w(w), h(h),
      tile_size(tile_size) {
  this->tiles.insert(this->tiles.begin(), tiles, tiles + w * h);
}
