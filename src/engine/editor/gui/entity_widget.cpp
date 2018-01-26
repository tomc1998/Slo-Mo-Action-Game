#include "entity_widget.hpp"
#include "gui.hpp"
#include "engine/editor/entity_type.hpp"
#include "engine/color.hpp"
#include "engine/renderer/paint_controller.hpp"

EntityWidget::EntityWidget(EntityType *entity_type, std::string *entity_name)
    : entity_type(entity_type), entity_name(entity_name) {}

void EntityWidget::update_paint(GuiContext &c, const Rect &rect,
                                const EditorInput &input) {
  static Color border(1.0f, 1.0f, 1.0f, 1.0f);
  static Color text(0.8f, 0.8f, 0.8f, 1.0f);
  c.p->draw_rect_hud(rect.pos.x, rect.pos.y, rect.size.x, rect.size.y, 1.5, &border);
}
