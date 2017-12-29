#include <glad/glad.h>

#include <GLFW/glfw3.h>

#include "engine/resource.hpp"
#include "engine/resource_manager.hpp"
#include "stb_image.h"
#include <iostream>

ResourceManager::ResourceManager() {
  unsigned char white_data[] = {
      255, 255, 255, 255,
  };

  // Cache this data & store in t
  Texture t;
  white = next_res_handle++;
  t.cache_tex_ix = tex_cache.cache_tex(white, white_data, 1, 1, t.uvs);
  handle_map[white] = Resource(t);
}

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

Texture *ResourceManager::lookup_tex(ResHandle handle) {
  auto r_it = handle_map.find(handle);
  if (r_it == handle_map.end()) {
    return NULL;
  }
  auto &r = r_it->second;
  assert(r.type == ResourceType::TEXTURE);
  return &r.data.texture;
}

void ResourceManager::bind_cache_tex(u64 cache_tex_ix) {
  glBindTexture(GL_TEXTURE_2D, tex_cache.cache_textures[cache_tex_ix]);
}

ResHandle ResourceManager::get_white() { return white; }
