#pragma once

#include "engine/renderer/paint_buffer.hpp"
#include "engine/renderer/batch.hpp"
#include "engine/animation.hpp"
#include "engine/texture.hpp"
#include "engine/resource_manager.hpp"

/**
 * A class created by the renderer, used for buffering vertex data before
 * rendering everything.
 *
 * # Rendering notes
 * Any rendering not involving a texture will use the 'white' texture, buffered
 * by default upon engine creation.
 */
class PaintController {
private:
  PaintBuffer *buffer;
  ResourceManager *res_manager;
  TexHandle white;
  /** The cache tex index for white - this is just to prevent unnecessary
   * lookups. */
  Texture* white_cache_tex;
  Batch curr_batch;

  /** Checks the current batch. If the texture currently loaded is equal to
   * cache_tex_ix, does nothing. Otherwise, flushes the batch to the renderer
   * and creates a new batch with the given cache tex ix. */
  void flush_if_batch_tex_not(u64 cache_tex_ix);

public:
  /** Create a new paint controller. See the Renderer class - paint
   * controllers should only be created via the gen_paint_controller method on
   * the renderer. */
  PaintController(PaintBuffer *_buffer, ResourceManager* r, TexHandle _white);

  void fill_rect(f32 x, f32 y, f32 w, f32 h, Color *color);
  void draw_line(Vec2 start, Vec2 end, f32 stroke, Color *color);
  void draw_animation(AnimHandle anim, u32 updates, f32 x, f32 y, f32 w, f32 h, f32 rot, Color *tint);
  void draw_image(TexHandle tex, f32 x, f32 y, f32 w, f32 h, f32 rotation, Color *tint);


  /** Draw some quads with the given vertices. This function will transform the
   * quads into 2 tris each. */
  void draw_quads(Vertex* v_buf, size_t num_quads, TexHandle tex);

  /** Convenience method for getting a texture from a resource handle. Useful
   * for when you need to know UVs, like with draw_quads. */
  Texture* get_tex_for_handle(TexHandle r);

  /** Flush the current batch if there's any vertices there, set the next batch
   * to have the same cache texture ix */
  void flush();
};
