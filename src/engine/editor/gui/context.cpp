#include "context.hpp"
#include "engine/renderer/paint_controller.hpp"

GuiContext::GuiContext(FontHandle default_font, PaintController *p)
    : default_font(default_font), p(p) {}
