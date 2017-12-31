#pragma once
#include "engine/renderer/tex_cache.hpp"
#include "engine/texture.hpp"
#include "engine/animation.hpp"
#include "engine/typedefs.hpp"
#include <sparsepp/spp.h>

class ResourceManager {
private:
  i32 next_res_handle = 0;
  spp::sparse_hash_map<TexHandle, Texture> tex_handle_map;
  spp::sparse_hash_map<AnimHandle, Animation> anim_handle_map;

  TexCache tex_cache;
  TexHandle white;

public:
  ResourceManager();

  /** Load a texture & return a handle to access that texture */
  TexHandle load_texture(const char *path);

  /** Lookup a texture, returning a pointer to it if it exists, or null
   * otherwise. Will assert if res is not a texture. */
  Texture *lookup_tex(TexHandle r);

  AnimHandle load_test_animation();

  /** Lookup an animation, returning a pointer to it if it exists, or null
   * otherwise. Will assert if res is not an animation */
  Animation *lookup_anim(AnimHandle a);

  /** Get a handle for the 'white' texture, a 1x1 texture which contains just
   * white and is used for coloured drawing. */
  TexHandle get_white();

  /** glBindTexture the cache texture at the given ix */
  void bind_cache_tex(u64 cache_tex_ix);
};
