#include <glad/glad.h>

#include <GLFW/glfw3.h>

#include "engine/animation.hpp"
#include "engine/resource_manager.hpp"
#include "engine/texture.hpp"
#include "engine/tileset.hpp"
#include "engine/util/io.hpp"
#include "json.hpp"
#include "stb_image.h"
#include <cstdio>
#include <fstream>
#include <iostream>
#include <sparsepp/spp.h>
#include <string>
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

void ResourceManager::load_texture_internal(const char *path, Texture *t,
                                            TexHandle th) {
  i32 w, h, n;
  void *data = (void *)stbi_load(path, &w, &h, &n, 4); // Load 4 channels rgba8

  // Cache this data & store in t
  t->cache_tex_ix = tex_cache.cache_tex(th, data, w, h, t->uvs);
}

TexHandle ResourceManager::load_texture(const char *path) {
  // Cache this data & store with a texhandle
  Texture t;
  TexHandle th = next_res_handle++;
  load_texture_internal(path, &t, th);
  tex_handle_map[th] = t;
  return th;
}

TilesetHandle ResourceManager::load_tileset(const char *path, u32 num_rows,
                                            u32 num_columns) {
  // Load a texture & use it to create a tileset
  Texture t;
  TilesetHandle th = next_res_handle++;
  load_texture_internal(path, &t, th);
  tileset_handle_map.insert({th, Tileset(t, num_rows, num_columns)});
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

Font *ResourceManager::lookup_font(FontHandle handle) {
  auto r_it = font_handle_map.find(handle);
  if (r_it == font_handle_map.end()) {
    return NULL;
  }
  return &r_it->second;
}

Tileset *ResourceManager::lookup_tileset(TilesetHandle handle) {
  auto r_it = tileset_handle_map.find(handle);
  if (r_it == tileset_handle_map.end()) {
    return NULL;
  }
  return &r_it->second;
}

FontHandle ResourceManager::load_font(const char *path) {
  std::vector<char *> lines = load_file_by_lines(path);
  Font f;
  u32 line_height = 0;
  u32 base = 0;
  u32 w = 0;
  u32 h = 0;
  char tex_name[100];
  std::sscanf(lines[1],
              "%*[^l]lineHeight=%u%*[^b]base=%u%*[^s]scaleW=%u%*[^s]scaleH=%u",
              &line_height, &base, &w, &h);
  std::sscanf(lines[2], "%*[^f]file=\"%[^\"]", tex_name);
  std::cout << tex_name << std::endl;
  f.line_height = line_height;
  f.base = base;

  TexHandle font_tex_h = next_res_handle++;

  this->load_texture_internal((const char *)tex_name, &f.tex, font_tex_h);
  f32 font_uvs[4] = {f.tex.uvs[0], f.tex.uvs[1], f.tex.uvs[2], f.tex.uvs[3]};

  for (u32 ii = 4; ii < lines.size(); ii++) {
    u32 id = 0;
    u32 x = 0;
    u32 y = 0;
    u32 width = 0;
    u32 height = 0;
    i32 x_offset = 0;
    i32 y_offset = 0;
    i32 x_advance = 0;

    std::sscanf(lines[ii], "%*sid=%u", &id);
    std::sscanf(lines[ii], "%*sx=%u", &x);
    std::sscanf(lines[ii], "%*sy=%u", &y);
    std::sscanf(lines[ii], "%*swidth=%u", &width);
    std::sscanf(lines[ii], "%*sheight=%u", &height);
    std::sscanf(lines[ii], "%*sxoffset=%d", &x_offset);
    std::sscanf(lines[ii], "%*syoffset=%d", &y_offset);
    std::sscanf(lines[ii], "%*sxadvance=%d", &x_advance);

    f32 uvs[] = {
        font_uvs[0] + (font_uvs[2] - font_uvs[0]) * (f32)x / (f32)w,
        font_uvs[1] + (font_uvs[3] - font_uvs[1]) * (f32)y / (f32)h,
        font_uvs[0] + (font_uvs[2] - font_uvs[0]) * (f32)(x + width) / (f32)w,
        font_uvs[2] + (font_uvs[3] - font_uvs[1]) * (f32)(y + height) / (f32)h,
    };

    f.char_map[char(id)] =
        Glyph(uvs, width, height, x_offset, y_offset, x_advance);
  }

  FontHandle fh = next_res_handle++;
  this->font_handle_map[fh] = f;
  return fh;
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
