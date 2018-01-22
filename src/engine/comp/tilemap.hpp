#pragma once
#include "engine/entity_id.hpp"
#include "engine/resource_defs.hpp"
#include "engine/vec.hpp"
#include <vector>

class CompTilemap {
public:
  /**
   * @param tiles See the `tiles` member, the length of this array should be
   * w*h
   */
  CompTilemap(EntityId entity_id, TilesetHandle tileset, Vec2 pos,
              u32 w, u32 h, Vec2 tile_size, u32 *tiles);

  CompTilemap();

  EntityId entity_id;

  /** The tileset to use */
  TilesetHandle tileset;

  /** The world position to render this tileset at */
  Vec2 pos;

  /** The width / height of this tilemap in tiles */
  u32 w, h;

  /** The size of the tiles in this tilemap in world units */
  Vec2 tile_size;

  /** The list of tiles. Each u32 references a position in a 2d array of w / h
   * the tileset columns / rows in row order - for example, 5 in a tileset of
   * width 4 would be the first tile in the 2nd row.
   */
  std::vector<u32> tiles;
};
