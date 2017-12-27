#include "engine/resource.hpp"
#include "engine/resource_manager.hpp"
#include "stb_image.h"

ResHandle ResourceManager::load_texture(const char *path) {
  i32 w, h, n;
  void *data = (void *)stbi_load(path, &w, &h, &n, 4); // Load 4 channels rgba8

  // Cache this data & store in t
  Texture t;
  ResHandle th = next_res_handle++;
  t.cache_tex_ix = tex_cache.cache_tex(th, data, w, h, t.uvs);

  handle_map[th] = Resource(t);

  return th;
}
