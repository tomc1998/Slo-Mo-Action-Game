#pragma once

#include "engine/renderer/paint_buffer.hpp"
#include "engine/renderer/batch.hpp"
#include "engine/resource.hpp"
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
  ResHandle white;
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
  PaintController(PaintBuffer *_buffer, ResourceManager* r, ResHandle _white);

  void fill_rect(f32 x, f32 y, f32 w, f32 h, Color *color);

  /** Flush the current batch if there's any vertices there, set the next batch
   * to have the same cache texture ix */
  void flush();
};
