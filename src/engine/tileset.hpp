#pragma once

#include "engine/texture.hpp"
#include "engine/vec.hpp"
#include <vector>

/** A class for a tileset resource. For a map of tiles (i.e. actual tile
 * positions in the world), see the Tilemap class.
 */
class Tileset {
private:
  /** The whole tileset as a texture */
  Texture tex;
  /** A cache of UV coordinates of all the tiles, generated when this
   * tileset is created. Given a tile coord (x, y), the index x*y in
   * this cache is the top-left UV coordinate of the tileset. */
  std::vector<Vec2> uv_cache;
  /** The size of the tile in UV coordinates */
  Vec2 tile_uv_size;

  /** Called by the constructors to populate the UV cache */
  void init_uv_cache();

public:
  /** The numbers of rows in the tile set */
  u32 num_rows;
  /** The number of columns in the tile set */
  u32 num_columns;

  /** Create a tileset over the given texture with the given size */
  Tileset(Texture tex, u32 num_rows, u32 num_columns);
  Tileset();

  /**
   * Get the UV coordinates for the given tile reference
   * @param[out] uvs - An array of 4 floats, containing the UV coords of the
   *                   upper left of the tile, and the UV coords of the lower
   *                   right of the tile
   * @param[in] x - The X position of the tile in the set - max value =
   *                num_columns-1
   * @param[in] y - The Y position of the tile in the set - max value =
   *                num_rows-1
   */
  void get_uv(f32 *uvs, u32 x, u32 y) const;

  /**
   * Given a tileset position x, y, get the tile at position x*y (where ix =
   * x*y). See get_uv method for more details.
   */
  void get_uv(f32 *uvs, u32 ix) const;

  /** Get the cache texture ix this tileset belongs to */
  u64 get_cache_tex() const;
};
