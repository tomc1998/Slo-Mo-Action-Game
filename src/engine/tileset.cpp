#include "engine/texture.hpp"
#include "engine/tileset.hpp"
#include "engine/vec.hpp"
#include <iostream>

void Tileset::init_uv_cache() {
  // Size of tile in tex coords
  tile_uv_size = Vec2((tex.uvs[2] - tex.uvs[0]) / num_columns,
                      (tex.uvs[3] - tex.uvs[1]) / num_rows);

  uv_cache.reserve(num_rows * num_columns);
  for (u32 jj = 0; jj < num_rows; ++jj) {
    for (u32 ii = 0; ii < num_columns; ++ii) {
      // Get UV position of tile
      Vec2 uv = Vec2(tex.uvs[0] + (f32)ii * tile_uv_size.x,
                     tex.uvs[1] + (f32)jj * tile_uv_size.y);
      uv_cache.push_back(uv);
    }
  }
}

Tileset::Tileset(Texture tex, u32 num_rows, u32 num_columns)
    : tex(tex), num_rows(num_rows), num_columns(num_columns) {
  init_uv_cache();
}
Tileset::Tileset() : num_rows(1), num_columns(1) { init_uv_cache(); }

void Tileset::get_uv(f32 *uvs, u32 x, u32 y) const { get_uv(uvs, x * y); }

void Tileset::get_uv(f32 *uvs, u32 ix) const {
  Vec2 pos0 = uv_cache[ix];
  Vec2 pos1 = pos0 + tile_uv_size;
  uvs[0] = pos0.x;
  uvs[1] = pos0.y;
  uvs[2] = pos1.x;
  uvs[3] = pos1.y;
}

u64 Tileset::get_cache_tex() const { return tex.cache_tex_ix; }
