#include "engine/comp/tilemap.hpp"
#include "engine/font.hpp"
#include "engine/glyph.hpp"
#include "engine/matrix.hpp"
#include "engine/renderer/paint_controller.hpp"
#include <cassert>
#include <cmath>
#include <cstring>
#include <iostream>
#include <vector>

PaintController::PaintController(PaintBuffer *_game_buffer,
                                 PaintBuffer *_hud_buffer,
                                 ResourceManager *_res_manager,
                                 TexHandle _white)
    : game_buffer(_game_buffer), hud_buffer(_hud_buffer),
      res_manager(_res_manager), white(_white),
      white_cache_tex(_res_manager->lookup_tex(_white)),
      curr_batch_game(Batch(white_cache_tex->cache_tex_ix)),
      curr_batch_hud(Batch(white_cache_tex->cache_tex_ix)) {}

void PaintController::flush_if_batch_tex_not(u64 cache_tex_ix,
                                             Batch &curr_batch,
                                             PaintBuffer *buffer) {
  if (curr_batch.tex == cache_tex_ix) {
    return;
  }
  if (curr_batch.vertices.size() > 0) {
    buffer->buffer(curr_batch);
  }
  curr_batch = Batch(cache_tex_ix);
}

void PaintController::flush(Batch &curr_batch, PaintBuffer *buffer) {
  if (curr_batch.vertices.size() > 0) {
    buffer->buffer(curr_batch);
  }
  curr_batch = Batch(curr_batch.tex);
}

Texture *PaintController::get_white_tex() { return white_cache_tex; }
TexHandle PaintController::get_white_tex_handle() { return white; }

void PaintController::fill_rect_internal(f32 x, f32 y, f32 w, f32 h,
                                         Color *color, Batch &curr_batch,
                                         PaintBuffer *buffer) {
  flush_if_batch_tex_not(white_cache_tex->cache_tex_ix, curr_batch, buffer);
  f32 *uvs = white_cache_tex->uvs;
  Vertex v[] = {Vertex(Vec2(x, y), color, Vec2(uvs[0], uvs[1])),
                Vertex(Vec2(x + w, y), color, Vec2(uvs[2], uvs[1])),
                Vertex(Vec2(x + w, y + h), color, Vec2(uvs[2], uvs[3])),

                Vertex(Vec2(x, y), color, Vec2(uvs[0], uvs[1])),
                Vertex(Vec2(x, y + h), color, Vec2(uvs[0], uvs[3])),
                Vertex(Vec2(x + w, y + h), color, Vec2(uvs[2], uvs[3]))};
  curr_batch.buffer(v, 6);
}

void PaintController::draw_tilemap_internal(CompTilemap const &tilemap,
                                            Color *tint, Batch &curr_batch,
                                            PaintBuffer *buffer) {
  // Create a vector and reserve the right amount of space for all the vertices
  std::vector<Vertex> v_buf;
  v_buf.reserve(tilemap.w * tilemap.h * 6);
  Tileset *tileset = res_manager->lookup_tileset(tilemap.tileset);
  for (u32 ii = 0; ii < tilemap.w; ++ii) {
    for (u32 jj = 0; jj < tilemap.h; ++jj) {
      u32 ix = ii + jj * tilemap.w;
      // Find the upper left & lower right positions of the tile
      Vec2 pos0(tilemap.pos.x + (tilemap.tile_size.x * ii),
                tilemap.pos.y + (tilemap.tile_size.y * jj));
      Vec2 pos1 = pos0 + tilemap.tile_size;
      // Find uvs
      f32 uvs[4];
      tileset->get_uv(uvs, tilemap.tiles[ix]);
      v_buf.push_back(Vertex(pos0, tint, Vec2(uvs[0], uvs[1])));
      v_buf.push_back(Vertex(Vec2(pos1.x, pos0.y), tint, Vec2(uvs[2], uvs[1])));
      v_buf.push_back(Vertex(pos1, tint, Vec2(uvs[2], uvs[3])));

      v_buf.push_back(Vertex(pos0, tint, Vec2(uvs[0], uvs[1])));
      v_buf.push_back(Vertex(Vec2(pos0.x, pos1.y), tint, Vec2(uvs[0], uvs[3])));
      v_buf.push_back(Vertex(pos1, tint, Vec2(uvs[2], uvs[3])));
    }
  }

  flush_if_batch_tex_not(tileset->get_cache_tex(), curr_batch, buffer);
  curr_batch.buffer(&v_buf[0], v_buf.size());
}

void PaintController::draw_line_internal(Vec2 start, Vec2 end, f32 stroke,
                                         Color *start_col, Color *end_col,
                                         Batch &curr_batch,
                                         PaintBuffer *buffer) {
  flush_if_batch_tex_not(white_cache_tex->cache_tex_ix, curr_batch, buffer);
  f32 *uvs = white_cache_tex->uvs;

  Vec2 inbetween = end - start;

  Vec2 left = start + Vec2(-inbetween.y, inbetween.x).nor() * stroke / 2;
  Vec2 right = start + Vec2(inbetween.y, -inbetween.x).nor() * stroke / 2;

  Vertex v[] = {Vertex(left, start_col, Vec2(uvs[0], uvs[1])),
                Vertex(left + inbetween, end_col, Vec2(uvs[2], uvs[1])),
                Vertex(right, start_col, Vec2(uvs[2], uvs[3])),

                Vertex(right, start_col, Vec2(uvs[0], uvs[1])),
                Vertex(right + inbetween, end_col, Vec2(uvs[0], uvs[3])),
                Vertex(left + inbetween, end_col, Vec2(uvs[2], uvs[3]))};
  curr_batch.buffer(v, 6);
}

void PaintController::draw_quads_internal(Vertex *v_buf, size_t num_quads,
                                          TexHandle tex, Batch &curr_batch,
                                          PaintBuffer *buffer) {
  flush_if_batch_tex_not(get_tex_for_handle(tex)->cache_tex_ix, curr_batch, buffer);
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

void PaintController::draw_animation_internal(AnimHandle anim, u32 updates,
                                              f32 x, f32 y, f32 w, f32 h,
                                              f32 rot, Color *tint,
                                              Batch &curr_batch,
                                              PaintBuffer *buffer) {
  assert(anim != -1);

  Animation *animation = this->res_manager->lookup_anim(anim);
  AnimFrame *frames = new AnimFrame[animation->get_part_count()];
  animation->get_anim_frames(updates, frames);

  for (u32 ii = 0; ii < animation->get_part_count(); ii++) {
    this->draw_image_internal(
        frames[ii].tex, x + frames[ii].posx - (frames[ii].scale - 1) * w / 2,
        y + frames[ii].posy - (frames[ii].scale - 1) * h / 2,
        w * frames[ii].scale, h * frames[ii].scale, rot + frames[ii].rot, tint,
        curr_batch, buffer);
  }
  delete[] frames;
}

void PaintController::draw_text_internal(const char *text, f32 x, f32 y,
                                         TextAlign align, FontHandle font,
                                         Color *color, Batch &curr_batch,
                                         PaintBuffer *buffer) {

  assert(font != -1);
  Font *f = this->res_manager->lookup_font(font);
  std::vector<Vertex> v_buf;
  v_buf.reserve(std::strlen(text) * 6);
  Vec2 cursor_pos;

  switch (align) {
  case BOT_LEFT:
    cursor_pos = Vec2(x, y - f->base);
    break;

  case BOT_CENTRE:
    cursor_pos = Vec2(x - f->get_width_for_text(text), y - f->base);
    break;

  case BOT_RIGHT:
    cursor_pos = Vec2(x - f->get_width_for_text(text) * 0.5, y - f->base);
    break;
  }

  for (u32 ii = 0; text[ii] != 0; ii++) {
    Glyph *g = &f->char_map[text[ii]];
    Vec2 offset_pos = cursor_pos + Vec2(g->x_offset, g->y_offset);
    v_buf.push_back(Vertex(offset_pos, color, Vec2(g->uvs[0], g->uvs[1])));
    v_buf.push_back(Vertex(offset_pos + Vec2(g->width, 0.0), color,
                           Vec2(g->uvs[2], g->uvs[1])));
    v_buf.push_back(Vertex(offset_pos + Vec2(g->width, g->height), color,
                           Vec2(g->uvs[2], g->uvs[3])));

    v_buf.push_back(Vertex(offset_pos, color, Vec2(g->uvs[0], g->uvs[1])));
    v_buf.push_back(Vertex(offset_pos + Vec2(0.0, g->height), color,
                           Vec2(g->uvs[0], g->uvs[3])));
    v_buf.push_back(Vertex(offset_pos + Vec2(g->width, g->height), color,
                           Vec2(g->uvs[2], g->uvs[3])));
    cursor_pos.x += g->x_advance;
  }

  flush_if_batch_tex_not(f->get_cache_tex(), curr_batch, buffer);
  curr_batch.buffer(&v_buf[0], v_buf.size());
}

void PaintController::draw_image_internal(TexHandle tex, f32 x, f32 y, f32 w,
                                          f32 h, f32 rotation, Color *tint,
                                          Batch &curr_batch,
                                          PaintBuffer *buffer) {
  // We don't want a null resource handle
  assert(tex != -1);

  Texture *texture = this->res_manager->lookup_tex(tex);

  this->flush_if_batch_tex_not(texture->cache_tex_ix, curr_batch, buffer);
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

void PaintController::fill_rect(f32 x, f32 y, f32 w, f32 h, Color *color) {
  fill_rect_internal(x, y, w, h, color, curr_batch_game, game_buffer);
}

void PaintController::fill_rect_hud(f32 x, f32 y, f32 w, f32 h, Color *color) {
  fill_rect_internal(x, y, w, h, color, curr_batch_hud, hud_buffer);
}

void PaintController::draw_line(Vec2 start, Vec2 end, f32 stroke,
                                Color *start_col, Color *end_col) {
  draw_line_internal(start, end, stroke, start_col, end_col, curr_batch_game,
            game_buffer);
}

void PaintController::draw_line_hud(Vec2 start, Vec2 end, f32 stroke,
                                    Color *start_col, Color *end_col) {
  draw_line_internal(start, end, stroke, start_col, end_col, curr_batch_hud, hud_buffer);
}

void PaintController::draw_animation(AnimHandle anim, u32 updates, f32 x, f32 y,
                                     f32 w, f32 h, f32 rot, Color *tint) {
  draw_animation_internal(anim, updates, x, y, w, h, rot, tint, curr_batch_game,
                          game_buffer);
}

void PaintController::draw_animation_hud(AnimHandle anim, u32 updates, f32 x,
                                         f32 y, f32 w, f32 h, f32 rot,
                                         Color *tint) {
  draw_animation_internal(anim, updates, x, y, w, h, rot, tint, curr_batch_hud,
                          hud_buffer);
}

void PaintController::draw_image(TexHandle tex, f32 x, f32 y, f32 w, f32 h,
                                 f32 rotation, Color *tint) {
  draw_image_internal(tex, x, y, w, h, rotation, tint, curr_batch_game,
                      game_buffer);
}

void PaintController::draw_image_hud(TexHandle tex, f32 x, f32 y, f32 w, f32 h,
                                     f32 rotation, Color *tint) {
  draw_image_internal(tex, x, y, w, h, rotation, tint, curr_batch_hud,
                      hud_buffer);
}

void PaintController::draw_quads(Vertex *v_buf, size_t num_quads,
                                 TexHandle tex) {
  draw_quads_internal(v_buf, num_quads, tex, curr_batch_game, game_buffer);
}

void PaintController::draw_quads_hud(Vertex *v_buf, size_t num_quads,
                                     TexHandle tex) {
  draw_quads_internal(v_buf, num_quads, tex, curr_batch_hud, hud_buffer);
}

void PaintController::draw_tilemap(CompTilemap const &tilemap, Color *tint) {
  draw_tilemap_internal(tilemap, tint, curr_batch_game, game_buffer);
}

void PaintController::draw_tilemap_hud(CompTilemap const &tilemap,
                                       Color *tint) {
  draw_tilemap_internal(tilemap, tint, curr_batch_hud, hud_buffer);
}

void PaintController::draw_text(const char *text, f32 x, f32 y, TextAlign align,
                                FontHandle font, Color *color) {
  draw_text_internal(text, x, y, align, font, color, curr_batch_game,
                     game_buffer);
}

void PaintController::draw_text_hud(const char *text, f32 x, f32 y,
                                    TextAlign align, FontHandle font,
                                    Color *color) {
  draw_text_internal(text, x, y, align, font, color, curr_batch_hud,
                     hud_buffer);
}
