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

void PaintController::draw_line(Vec2 start, Vec2 end, f32 stroke, Color *color) {
  flush_if_batch_tex_not(white_cache_tex->cache_tex_ix);
  f32 *uvs = white_cache_tex->uvs;

  Vec2 inbetween = end - start;

  Vec2 left = start + Vec2(-inbetween.y, inbetween.x).nor() * stroke/2;
  Vec2 right = start + Vec2(inbetween.y, -inbetween.x).nor() * stroke/2;

  Vertex v[] = {Vertex(left, color, Vec2(uvs[0], uvs[1])),
                Vertex(left + inbetween, color, Vec2(uvs[2], uvs[1])),
                Vertex(right, color, Vec2(uvs[2], uvs[3])),

                Vertex(right, color, Vec2(uvs[0], uvs[1])),
                Vertex(right + inbetween, color, Vec2(uvs[0], uvs[3])),
                Vertex(left + inbetween, color, Vec2(uvs[2], uvs[3]))};
  curr_batch.buffer(v, 6);
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

Texture* PaintController::get_tex_for_handle(TexHandle r) {
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

  Vec2 newPoints[4] = {
      rot_matrix.mul(translated) + centre,
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
