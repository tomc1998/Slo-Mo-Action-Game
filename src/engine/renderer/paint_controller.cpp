#include "engine/matrix.hpp"
#include "engine/renderer/paint_controller.hpp"
#include <cassert>
#include <cmath>
#include <iostream>

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

void PaintController::draw_animation(AnimHandle ah, u32 updates,
                                     f32 x, f32 y, f32 w, f32 h, f32 rot, Color *tint) {
  assert(ah != -1);

  Animation *anim = this->res_manager->lookup_anim(ah);
  AnimFrame *frames = new AnimFrame[anim->get_part_count()];
  anim->get_anim_frames(updates, frames);

  for (u32 ii = 0; ii < anim->get_part_count(); ii++) {
    this->draw_image(frames[ii].th, x + frames[ii].posx, y + frames[ii].posy,
                     w * frames[ii].scale, h * frames[ii].scale,
                     rot + frames[ii].rot, tint);
  }
  delete[] frames;
}

void PaintController::draw_image(TexHandle th, f32 x, f32 y, f32 w, f32 h,
                                 f32 rotation, Color *tint) {
  // We don't want a null resource handle
  assert(th != -1);

  Texture *tex = this->res_manager->lookup_tex(th);

  this->flush_if_batch_tex_not(tex->cache_tex_ix);
  f32 *uvs = tex->uvs;
  Vec2 centre = Vec2(x + w / 2, y + h / 2);
  Vec2 translated = Vec2(x - centre.x, y - centre.y);
  Matrix2x2 rot_matrix(std::cos(rotation), -1 * std::sin(rotation),
                       std::sin(rotation), std::cos(rotation));

  Vec2 newPoints[4] = {
      rot_matrix.multiply_by_vec(translated).add(centre),
      rot_matrix.multiply_by_vec(translated.add(Vec2(w, 0.0))).add(centre),
      rot_matrix.multiply_by_vec(translated.add(Vec2(0.0, h))).add(centre),
      rot_matrix.multiply_by_vec(translated.add(Vec2(w, h))).add(centre)};

  Vertex v[] = {Vertex(newPoints[0], tint, Vec2(uvs[0], uvs[1])),
                Vertex(newPoints[1], tint, Vec2(uvs[2], uvs[1])),
                Vertex(newPoints[3], tint, Vec2(uvs[2], uvs[3])),

                Vertex(newPoints[0], tint, Vec2(uvs[0], uvs[1])),
                Vertex(newPoints[2], tint, Vec2(uvs[0], uvs[3])),
                Vertex(newPoints[3], tint, Vec2(uvs[2], uvs[3]))};
  curr_batch.buffer(v, 6);
}
