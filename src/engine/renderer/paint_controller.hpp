#pragma once

#include "engine/renderer/paint_buffer.hpp"

/**
 * A class created by the renderer, used for buffering vertex data before
 * rendering everything.
 */
class PaintController {
private:
  PaintBuffer *buffer;

public:
  /** Create a new paint controller. See the Renderer class - paint
   * controllers should only be created via the gen_paint_controller method on
   * the renderer. */
  PaintController(PaintBuffer *_buffer);

  void fill_rect(f32 x, f32 y, f32 w, f32 h, Color *color);
};
