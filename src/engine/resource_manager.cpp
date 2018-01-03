#include <glad/glad.h>

#include <GLFW/glfw3.h>

#include "engine/animation.hpp"
#include "engine/resource_manager.hpp"
#include "engine/texture.hpp"
#include "stb_image.h"
#include "json.hpp"
#include <fstream>
#include <iostream>
#include <sparsepp/spp.h>
using json = nlohmann::json;

ResourceManager::ResourceManager() {
  unsigned char white_data[] = {
      255,
      255,
      255,
      255,
  };

  // Cache this data & store in t
  Texture t;
  white = next_res_handle++;
  t.cache_tex_ix = tex_cache.cache_tex(white, white_data, 1, 1, t.uvs);
  tex_handle_map[white] = t;
}

TexHandle ResourceManager::load_texture(const char *path) {
  i32 w, h, n;
  void *data = (void *)stbi_load(path, &w, &h, &n, 4); // Load 4 channels rgba8

  // Cache this data & store in t
  Texture t;
  TexHandle th = next_res_handle++;
  t.cache_tex_ix = tex_cache.cache_tex(th, data, w, h, t.uvs);

  tex_handle_map[th] = t;

  return th;
}

Texture *ResourceManager::lookup_tex(TexHandle handle) {
  auto r_it = tex_handle_map.find(handle);
  if (r_it == tex_handle_map.end()) {
    return NULL;
  }
  return &r_it->second;
}

/** Takes a path to a json file which contains keyframes exported by the python
 * blender exporter. Also takes in a reference to a vector of TexHandles to
 * store in the animation. Returns an animation handle */
AnimHandle ResourceManager::load_animation(const char *path,
                                           std::vector<TexHandle> &texs) {
  std::ifstream i(path);
  json j;
  i >> j;

  Animation a = j;

  a.assign_parts(texs);

  AnimHandle anim = next_res_handle++;

  anim_handle_map[anim] = a;

  return anim;
}


Animation *ResourceManager::lookup_anim(AnimHandle a) {
  auto r_it = anim_handle_map.find(a);
  if (r_it == tex_handle_map.end()) {
    return NULL;
  }
  return &r_it->second;
}

void ResourceManager::bind_cache_tex(u64 cache_tex_ix) {
  glBindTexture(GL_TEXTURE_2D, tex_cache.cache_textures[cache_tex_ix]);
}

TexHandle ResourceManager::get_white() { return white; }
