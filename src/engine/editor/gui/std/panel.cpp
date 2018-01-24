#include "panel.hpp"
#include "engine/renderer/paint_controller.hpp"
#include "engine/color.hpp"

void paint_panel(PaintController& p, Rect rect) {
  Color black(0.0, 0.0, 0.0, 1.0);
  p.fill_rect_hud(rect.pos.x, rect.pos.y, rect.size.x, rect.size.y, &black);
}
