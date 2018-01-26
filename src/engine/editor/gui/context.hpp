#pragma once

#include "engine/resource_defs.hpp"

class PaintController;

/** A context object containing standard textures, fonts, and a pointer to a
 * paint controller for rendering the GUI. */
class GuiContext {
  public:
  const FontHandle default_font;
  PaintController* p;
  GuiContext(FontHandle default_font, PaintController* p);
};
