#include "engine/color.hpp"
#include "engine/editor/gui/gui.hpp"
#include "engine/renderer/paint_controller.hpp"
#include "panel.hpp"
#include <cassert>

Rect paint_panel(GuiContext &g, const BoxConstraints &rect) {
  assert(rect.size.x >= 0 && rect.size.y >= 0 &&
         "Painting panel with unconstrained constraints");
  Color black(0.0, 0.0, 0.0, 1.0);
  g.p->fill_rect_hud(rect.pos.x, rect.pos.y, rect.size.x, rect.size.y, &black);
  return rect;
}
