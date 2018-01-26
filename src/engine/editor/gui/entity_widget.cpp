#include "entity_widget.hpp"
#include "gui.hpp"
#include "engine/editor/entity_type.hpp"
#include "engine/color.hpp"
#include "engine/renderer/paint_controller.hpp"

EntityWidget::EntityWidget(EntityType *entity_type, std::string *entity_name)
    : entity_type(entity_type), entity_name(entity_name) {}

void EntityWidget::update_paint(PaintController &p, const Rect &rect,
                                const EditorInput &input) {
  static Color ui_bg(1.0f, 0.0f, 0.0f, 1.0f);
  p.fill_rect_hud(rect.pos.x, rect.pos.y, rect.size.x, rect.size.y, &ui_bg);
}
