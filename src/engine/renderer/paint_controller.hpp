#pragma once

#include "engine/renderer/batch.hpp"
#include "engine/resource_defs.hpp"
#include "engine/editor/gui/common.hpp"

class ResourceManager;
class PaintBuffer;
class Texture;
class CompTilemap;

/**
 * A class created by the renderer, used for buffering vertex data before
 * rendering everything.
 *
 * # Rendering notes
 * Any rendering not involving a texture will use the 'white' texture, buffered
 * by default upon engine creation.
 */
class PaintController {
  friend class Engine;
private:
  PaintBuffer *game_buffer;
  PaintBuffer *hud_buffer;
  ResourceManager *res_manager;
  TexHandle white;
  /** The cache tex index for white - this is just to prevent unnecessary
   * lookups. */
  Texture *white_cache_tex;
  Batch curr_batch_game;
  Batch curr_batch_hud;

  bool using_clip = false;
  Rect curr_clip = Rect(0.0, 0.0, 0.0, 0.0);

  /** Clip the given vertex list rect by the curr_clip, if using_clip is set. 
   * @param v Should be of length 6, with 2 triangles making up a rectangle.
   *          The rectangle should be split from top left to bottom right. (see
   *          how fill_rect_internal splits the rect for more details)
   */
  void clip_v_buf_rect(Vertex *v);

  /** Checks the current batch. If the texture currently loaded is equal to
   * cache_tex_ix, does nothing. Otherwise, flushes the batch to the renderer
   * and creates a new batch with the given cache tex ix. */
  void flush_if_batch_tex_not(u64 cache_tex_ix, Batch &curr_batch, PaintBuffer *buffer);

  void draw_rect_internal(f32 x, f32 y, f32 w, f32 h, f32 thickness, Color *color,
                          Batch &curr_batch, PaintBuffer *buffer);
  void fill_rect_internal(f32 x, f32 y, f32 w, f32 h, Color *color,
                          Batch &curr_batch, PaintBuffer *buffer);
  void draw_line_internal(Vec2 start, Vec2 end, f32 stroke, Color *start_col,
                          Color *end_col, Batch &curr_batch, PaintBuffer *buffer);
  void draw_animation_internal(AnimHandle anim, u32 updates, f32 x, f32 y,
                               f32 w, f32 h, f32 rot, Color *tint,
                               Batch &curr_batch, PaintBuffer *buffer);
  void draw_image_internal(TexHandle tex, f32 x, f32 y, f32 w, f32 h,
                           f32 rotation, Color *tint, Batch &curr_batch, PaintBuffer *buffer);

  /** Draw some quads with the given vertices. This function will transform the
   * quads into 2 tris each. */
  void draw_quads_internal(Vertex *v_buf, size_t num_quads, TexHandle tex,
                           Batch &curr_batch, PaintBuffer *buffer);

  /** Draw some quads with the given vertices. This function will transform the
   * quads into 2 tris each. */
  void draw_tris_internal(Vertex *v_buf, size_t num_tris, TexHandle tex,
                           Batch &curr_batch, PaintBuffer *buffer);

  void draw_tilemap_internal(CompTilemap const &tilemap, Color *tint,
                             Batch &curr_batch, PaintBuffer *buffer);

  /** Draws a line of text, given the x and y position and alignment
   *
   * The x and y position will not always reference the same thing, it depends
   * on the alignment. E.g. BOT_LEFT alignment will specify the bottom and left
   * of the line, whereas BOT_CENTRE will specify the bottom and the centre of
   * the line.
   *
   * */
  void draw_text_internal(const char *text, f32 x, f32 y, TextAlign align,
                          FontHandle font, Color *color, Batch &curr_batch, PaintBuffer *buffer);

public:
  /** Create a new paint controller. See the Renderer class - paint
   * controllers should only be created via the gen_paint_controller method on
   * the renderer. */
  PaintController(PaintBuffer *_game_buffer, PaintBuffer *_hud_buffer,
                  ResourceManager *r, TexHandle _white);

  void set_clip(Rect r);
  void clear_clip();
  Rect* get_clip();

  void fill_rect(f32 x, f32 y, f32 w, f32 h, Color *color);
  void fill_rect_hud(f32 x, f32 y, f32 w, f32 h, Color *color);

  void draw_rect(f32 x, f32 y, f32 w, f32 h, f32 thickness, Color *color);
  void draw_rect_hud(f32 x, f32 y, f32 w, f32 h, f32 thickness, Color *color);

  void draw_line(Vec2 start, Vec2 end, f32 stroke, Color *start_col,
                 Color *end_col);
  void draw_line_hud(Vec2 start, Vec2 end, f32 stroke, Color *start_col,
                     Color *end_col);

  void draw_animation(AnimHandle anim, u32 updates, f32 x, f32 y, f32 w, f32 h,
                      f32 rot, Color *tint);
  void draw_animation_hud(AnimHandle anim, u32 updates, f32 x, f32 y, f32 w,
                          f32 h, f32 rot, Color *tint);

  void draw_image(TexHandle tex, f32 x, f32 y, f32 w, f32 h, f32 rotation,
                  Color *tint);
  void draw_image_hud(TexHandle tex, f32 x, f32 y, f32 w, f32 h, f32 rotation,
                      Color *tint);
  void draw_quads(Vertex *v_buf, size_t num_quads, TexHandle tex);
  void draw_quads_hud(Vertex *v_buf, size_t num_quads, TexHandle tex);

  void draw_tris(Vertex *v_buf, size_t num_quads, TexHandle tex);
  void draw_tris_hud(Vertex *v_buf, size_t num_quads, TexHandle tex);

  void draw_tilemap(CompTilemap const &tilemap, Color *tint);
  void draw_tilemap_hud(CompTilemap const &tilemap, Color *tint);

  void draw_text(const char *text, f32 x, f32 y, TextAlign align,
                 FontHandle font, Color *color);
  void draw_text_hud(const char *text, f32 x, f32 y, TextAlign align,
                     FontHandle font, Color *color);
  /** Convenience method for getting a texture from a resource handle. Useful
   * for when you need to know UVs, like with draw_quads. */
  Texture *get_tex_for_handle(TexHandle r);

  Texture *get_white_tex();
  TexHandle get_white_tex_handle();

  /** Flush the current batch if there's any vertices there, set the next batch
   * to have the same cache texture ix */
  void flush(Batch &curr_batch, PaintBuffer *buffer);
};
