#include <glad/glad.h>

#include <GLFW/glfw3.h>

#include "engine/animation.hpp"
#include "engine/resource_manager.hpp"
#include "engine/texture.hpp"
#include "stb_image.h"

#include "json.hpp"
using json = nlohmann::json;

#include <iostream>
#include <fstream>
#include <sparsepp/spp.h>

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

void from_json(const json &j, Animation &a) {

  spp::sparse_hash_map<std::string, InterpolationType> interp_map =
  { {"LINEAR", LINEAR} };

  // Loops through all the part ids
  for (u32 part_id=0; part_id < j.size(); part_id++) {

    // Creates a json variable that stores the posx keys etc for this part
    const json &keys = j.at(std::to_string(part_id));

    const json &posx = keys.at("posx");
    for (u32 ii = 0; ii < posx.size(); ii++) {
      a.posx_keys.push_back(
          Keyframe(posx[ii].at("value"), posx[ii].at("timestamp"),
                   interp_map[posx[ii].at("interpolation")], part_id));
    }

    const json &posy = keys.at("posy");
    for (u32 ii = 0; ii < posy.size(); ii++) {
      a.posy_keys.push_back(
          Keyframe(posy[ii].at("value"), posy[ii].at("timestamp"),
                   interp_map[posy[ii].at("interpolation")], part_id));
    }

    const json &scale = keys.at("scale");
    for (u32 ii = 0; ii < scale.size(); ii++) {
      a.scale_keys.push_back(
          Keyframe(scale[ii].at("value"), scale[ii].at("timestamp"),
                   interp_map[scale[ii].at("interpolation")], part_id));
    }

    const json &rot = keys.at("rotation");
    for (u32 ii = 0; ii < rot.size(); ii++) {
      a.rot_keys.push_back(
          Keyframe(rot[ii].at("value"), rot[ii].at("timestamp"),
                   interp_map[rot[ii].at("interpolation")], part_id));
    }
  }
}
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


Texture *ResourceManager::lookup_tex(TexHandle handle) {
  auto r_it = tex_handle_map.find(handle);
  if (r_it == tex_handle_map.end()) {
    return NULL;
  }
  return &r_it->second;
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
