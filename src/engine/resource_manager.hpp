#pragma once
#include "engine/renderer/tex_cache.hpp"
#include "engine/resource.hpp"
#include "engine/typedefs.hpp"
#include <sparsepp/spp.h>

class ResourceManager {
private:
  ResHandle next_res_handle = 0;
  spp::sparse_hash_map<ResHandle, Resource> handle_map;

  TexCache tex_cache;
  ResHandle white;

public:
  ResourceManager();

  /** Load a texture & return a handle to access that texture */
  ResHandle load_texture(const char *path);

  /** Lookup a texture, returning a pointer to it if it exists, or null
   * otherwise. Will assert if res is not a texture. */
  Texture* lookup_tex(ResHandle r);

  /** Get a handle for the 'white' texture, a 1x1 texture which contains just
   * white and is used for coloured drawing. */
  ResHandle get_white();

  /** glBindTexture the cache texture at the given ix */
  void bind_cache_tex(u64 cache_tex_ix);
};
