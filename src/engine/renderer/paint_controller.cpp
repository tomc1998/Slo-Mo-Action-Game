#include "engine/matrix.hpp"
#include "engine/renderer/paint_controller.hpp"
#include "engine/comp/tilemap.hpp"
#include <cassert>
#include <cmath>
#include <iostream>
#include <vector>

PaintController::PaintController(PaintBuffer *_buffer,
                                 ResourceManager *_res_manager,
                                 TexHandle _white)
    : buffer(_buffer), res_manager(_res_manager), white(_white),
      white_cache_tex(_res_manager->lookup_tex(_white)),
      curr_batch(Batch(white_cache_tex->cache_tex_ix)) {}

void PaintController::flush_if_batch_tex_not(u64 cache_tex_ix) {
  if (curr_batch.tex == cache_tex_ix) {
    return;
  }
  if (curr_batch.vertices.size() > 0) {
    buffer->buffer(curr_batch);
  }
  curr_batch = Batch(cache_tex_ix);
}

void PaintController::flush() {
  if (curr_batch.vertices.size() > 0) {
    buffer->buffer(curr_batch);
  }
  curr_batch = Batch(curr_batch.tex);
}

void PaintController::fill_rect(f32 x, f32 y, f32 w, f32 h, Color *color) {
  flush_if_batch_tex_not(white_cache_tex->cache_tex_ix);
  f32 *uvs = white_cache_tex->uvs;
  Vertex v[] = {Vertex(Vec2(x, y), color, Vec2(uvs[0], uvs[1])),
                Vertex(Vec2(x + w, y), color, Vec2(uvs[2], uvs[1])),
                Vertex(Vec2(x + w, y + h), color, Vec2(uvs[2], uvs[3])),

                Vertex(Vec2(x, y), color, Vec2(uvs[0], uvs[1])),
                Vertex(Vec2(x, y + h), color, Vec2(uvs[0], uvs[3])),
                Vertex(Vec2(x + w, y + h), color, Vec2(uvs[2], uvs[3]))};
  curr_batch.buffer(v, 6);
}

void PaintController::draw_tilemap(CompTilemap const &tilemap, Color *tint) {
  // Create a vector and reserve the right amount of space for all the vertices
  std::vector<Vertex> v_buf;
  v_buf.reserve(tilemap.w * tilemap.h * 6);
  Tileset* tileset = res_manager->lookup_tileset(tilemap.tileset);
  for (u32 ii = 0; ii < tilemap.w; ++ii) {
    for (u32 jj = 0; jj < tilemap.h; ++jj) {
      u32 ix = ii+jj*tilemap.w;
      // Find the upper left & lower right positions of the tile
      Vec2 pos0(tilemap.pos.x + (tilemap.tile_size.x * ii),
               tilemap.pos.y + (tilemap.tile_size.y * jj));
      Vec2 pos1 = pos0 + tilemap.tile_size;
      // Find uvs
      f32 uvs[4];
      tileset->get_uv(uvs, tilemap.tiles[ix]);
      v_buf.push_back(Vertex(pos0,                 tint, Vec2(uvs[0], uvs[1])));
      v_buf.push_back(Vertex(Vec2(pos1.x, pos0.y), tint, Vec2(uvs[2], uvs[1])));
      v_buf.push_back(Vertex(pos1,            tint, Vec2(uvs[2], uvs[3])));

      v_buf.push_back(Vertex(pos0,                 tint, Vec2(uvs[0], uvs[1])));
      v_buf.push_back(Vertex(Vec2(pos0.x, pos1.y), tint, Vec2(uvs[0], uvs[3])));
      v_buf.push_back(Vertex(pos1,            tint, Vec2(uvs[2], uvs[3])));
    }
  }

  flush_if_batch_tex_not(tileset->get_cache_tex());
  curr_batch.buffer(&v_buf[0], v_buf.size());
}

void PaintController::draw_quads(Vertex *v_buf, size_t num_quads,
                                 TexHandle tex) {
  flush_if_batch_tex_not(get_tex_for_handle(tex)->cache_tex_ix);
  std::vector<Vertex> vertices;
  vertices.reserve(num_quads * 6);
  ;
  for (u32 ii = 0; ii < num_quads * 4; ii += 4) {
    Vertex v[] = {v_buf[ii], v_buf[ii + 1], v_buf[ii + 2],
                  v_buf[ii], v_buf[ii + 3], v_buf[ii + 2]};
    vertices.insert(vertices.end(), v, v + 6);
  }
  curr_batch.buffer(&(vertices[0]), vertices.size());
}

Texture *PaintController::get_tex_for_handle(TexHandle r) {
  return res_manager->lookup_tex(r);
}

void PaintController::draw_animation(AnimHandle anim, u32 updates, f32 x, f32 y,
                                     f32 w, f32 h, f32 rot, Color *tint) {
  assert(anim != -1);

  Animation *animation = this->res_manager->lookup_anim(anim);
  AnimFrame *frames = new AnimFrame[animation->get_part_count()];
  animation->get_anim_frames(updates, frames);

  for (u32 ii = 0; ii < animation->get_part_count(); ii++) {
    this->draw_image(
        frames[ii].tex, x + frames[ii].posx - (frames[ii].scale - 1) * w / 2,
        y + frames[ii].posy - (frames[ii].scale - 1) * h / 2,
        w * frames[ii].scale, h * frames[ii].scale, rot + frames[ii].rot, tint);
  }
  delete[] frames;
}

void PaintController::draw_image(TexHandle tex, f32 x, f32 y, f32 w, f32 h,
                                 f32 rotation, Color *tint) {
  // We don't want a null resource handle
  assert(tex != -1);

  Texture *texture = this->res_manager->lookup_tex(tex);

  this->flush_if_batch_tex_not(texture->cache_tex_ix);
  f32 *uvs = texture->uvs;
  Vec2 centre = Vec2(x + w / 2, y + h / 2);
  Vec2 translated = Vec2(x - centre.x, y - centre.y);
  Matrix2x2 rot_matrix(std::cos(rotation), -1 * std::sin(rotation),
                       std::sin(rotation), std::cos(rotation));

  Vec2 newPoints[4] = {rot_matrix.mul(translated) + centre,
                       rot_matrix.mul(translated + Vec2(w, 0.0)) + centre,
                       rot_matrix.mul(translated + Vec2(0.0, h)) + centre,
                       rot_matrix.mul(translated + Vec2(w, h)) + centre};

  Vertex v[] = {Vertex(newPoints[0], tint, Vec2(uvs[0], uvs[1])),
                Vertex(newPoints[1], tint, Vec2(uvs[2], uvs[1])),
                Vertex(newPoints[3], tint, Vec2(uvs[2], uvs[3])),

                Vertex(newPoints[0], tint, Vec2(uvs[0], uvs[1])),
                Vertex(newPoints[2], tint, Vec2(uvs[0], uvs[3])),
                Vertex(newPoints[3], tint, Vec2(uvs[2], uvs[3]))};
  curr_batch.buffer(v, 6);
}
