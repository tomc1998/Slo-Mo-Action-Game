#include "engine/renderer/paint_controller.hpp"

PaintController::PaintController(PaintBuffer *_buffer,
                                 ResourceManager *_res_manager,
                                 ResHandle _white)
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
