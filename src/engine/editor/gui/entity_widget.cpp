#include "engine/color.hpp"
#include "engine/editor/entity_type.hpp"
#include "engine/renderer/paint_controller.hpp"
#include "entity_widget.hpp"
#include "gui.hpp"
#include <cassert>
#include <cstring>

EntityWidget::EntityWidget(const EntityType *entity_type, const char* entity_name)
    : entity_type(entity_type) {
  assert(strlen(entity_name) < 31 && "Entity name too long for entity widget");
  strcpy(this->entity_name, entity_name);
}

void EntityWidget::update_paint(GuiContext &c, const Rect &rect,
                                const EditorInput &input) {
  static Color border(1.0f, 1.0f, 1.0f, 1.0f);
  static Color text(0.8f, 0.8f, 0.8f, 1.0f);
  c.p->draw_rect_hud(rect.pos.x, rect.pos.y - 40, rect.size.x, rect.size.y, 2.0,
                     &border);
  c.p->draw_text_hud(entity_name, rect.centre_x(), rect.bottom(),
                     TextAlign::BOT_CENTRE, c.default_font, &text);
}
