#include "entity_widget.hpp"
#include "engine/color.hpp"
#include "engine/editor/entity_type.hpp"
#include "engine/renderer/paint_controller.hpp"
#include "gui.hpp"
#include <cassert>
#include <cstring>

EntityWidget::EntityWidget(const EntityType *entity_type,
                           const char *entity_name)
    : entity_type(entity_type) {
  assert(strlen(entity_name) < 31 && "Entity name too long for entity widget");
  strcpy(this->entity_name, entity_name);
}

void EntityWidget::update_paint(GuiContext &c, const BoxConstraints &rect,
                                const EditorInput &input) {
  static Color border(1.0f, 1.0f, 1.0f, 1.0f);
  static Color text(0.8f, 0.8f, 0.8f, 1.0f);
  c.p->draw_rect_hud(rect.left() + 20, rect.top(), rect.size.x - 40,
                     rect.size.y - 40, 2.0, &border);
  c.p->draw_text_hud(entity_name, rect.centre_x(), rect.bottom(),
                     TextAlign::BOT_CENTRE, c.default_font, &text);
  if (entity_type->sprite) {
    c.p->draw_image_hud(entity_type->sprite->tex, rect.left() + 20, rect.top(),
                        rect.size.x - 40, rect.size.y - 40, 0, &border);
  }
}
