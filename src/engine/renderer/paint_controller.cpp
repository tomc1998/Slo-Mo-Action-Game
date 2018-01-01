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

void PaintController::draw_quads(Vertex *v_buf, size_t num_quads,
                                 ResHandle tex) {
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

Texture* PaintController::get_tex_for_handle(ResHandle r) {
  return res_manager->lookup_tex(r);
}

