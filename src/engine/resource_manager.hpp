#pragma once
#include "engine/animation.hpp"
#include "engine/font.hpp"
#include "engine/renderer/tex_cache.hpp"
#include "engine/texture.hpp"
#include "engine/tileset.hpp"
#include "engine/typedefs.hpp"
#include <sparsepp/spp.h>

/**
 * Additional Notes:
 * In the texture cache, tileset textures have the same handle as the tileset
 * (so if a tileset has a TilesetHandle of 4, then the texture it references
 * will also have a handle of 4.
 */
class ResourceManager {
private:
  i32 next_res_handle = 0;
  spp::sparse_hash_map<TexHandle, Texture> tex_handle_map;
  spp::sparse_hash_map<AnimHandle, Animation> anim_handle_map;
  spp::sparse_hash_map<TilesetHandle, Tileset> tileset_handle_map;
  spp::sparse_hash_map<FontHandle, Font> font_handle_map;

  /** Texture cache mapping texhandles to rects. */
  TexCache tex_cache;
  TexHandle white;

  /**
   * Utility function to load a texture into the cache & return the UVs
   * @param[out] t Where to store the resulting UVs
   */
  void load_texture_internal(const char *path, Texture *t, TexHandle th);

public:
  ResourceManager();

  /** Load a texture & return a handle to access that texture */
  TexHandle load_texture(const char *path);

  /** Load a tileset.
   *
   * The resultant tilesethandle can also be used to lookup the whole texture
   * of the tileset with lookup_tex (though this is just a result of the code
   * written, and shouldn't be relied on).
   * @param path The path to the image containing the tileset
   * @param num_rows The number of tile rows in the tileset
   * @param num_columns The number of tile columns in the tileset
   */
  TilesetHandle load_tileset(const char *path, u32 num_rows, u32 num_columns);

  /** Lookup an animation, returning a pointer to it if it exists, or null
   * otherwise. Will assert if res is not an animation */
  Tileset *lookup_tileset(TilesetHandle a);

  /** Lookup a texture, returning a pointer to it if it exists, or null
   * otherwise. Will assert if res is not a texture. */
  Texture *lookup_tex(TexHandle r);

  /** Lookup a font, returning a pointer to it if it exists, or null otherwise.
   * Will assert if res is not a font */
  Font *lookup_font(FontHandle r);

  AnimHandle load_animation(const char *path, std::vector<TexHandle> &texs);

  /** Lookup an animation, returning a pointer to it if it exists, or null
   * otherwise. Will assert if res is not an animation */
  Animation *lookup_anim(AnimHandle a);

  /** Get a handle for the 'white' texture, a 1x1 texture which contains just
   * white and is used for coloured drawing. */
  TexHandle get_white();

  /** glBindTexture the cache texture at the given ix */
  void bind_cache_tex(u64 cache_tex_ix);
};
