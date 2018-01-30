#include "engine/color.hpp"
#include "engine/input/input_state.hpp"
#include "engine/renderer/paint_controller.hpp"
#include "engine/renderer/vertex.hpp"
#include "engine/resource_defs.hpp"
#include "engine/system/globals.hpp"
#include "entity_type_manager.hpp"
#include "input.hpp"
#include <iostream>
#include <iterator>
#include <utility>

void EntityTypeManager::insert_entity_type(std::string name, EntityType* type) {
  entity_type_map[name] = type;
  entity_widget_list.push_back(EntityWidget(type, name.c_str()));
}

void EntityTypeManager::delete_entity_type(std::string name) {
  entity_type_map.erase(name);
  for (u32 ii = 0; ii < entity_widget_list.size(); ++ii) {
    if (entity_widget_list[ii].entity_name == name) {
      entity_widget_list.erase(entity_widget_list.begin() + ii);
      break;
    }
  }
}

EntityType* EntityTypeManager::get_entity_type(std::string name) {
  return entity_type_map[name];
}

void EntityTypeManager::paint(GuiContext &c, const Rect &rect,
                              const EditorInput &input) {
  const auto pc = c.p;
  static Color ui_bg(0.0f, 0.0f, 0.0f, 1.0f);
  static Color ui_fg(1.0f, 1.0f, 1.0f, 1.0f);
  paint_panel(c, rect);

  // Split entities into pages, then render the current page
  const static f32 HORI_PADDING = 60.0f;
  const static f32 VERT_PADDING = 40.0f;
  const static f32 ENTITY_PADDING = 5.0f;
  const static f32 ENTITY_SIZE = 150.0f;
  static u32 ENTITIES_PER_PAGE =
      (rect.size.x - HORI_PADDING * 2.f) / ENTITY_SIZE;
  const u32 entity_start_ix = curr_page * ENTITIES_PER_PAGE;
  for (u32 ii = entity_start_ix; ii < entity_start_ix + ENTITIES_PER_PAGE &&
                                 ii < entity_widget_list.size();
       ++ii) {
    entity_widget_list[ii].update_paint(
        c, Rect(rect.pos.x + HORI_PADDING + (ii - entity_start_ix) * ENTITY_SIZE +
                          ENTITY_PADDING,
                      rect.pos.y + VERT_PADDING + ENTITY_PADDING,
                      ENTITY_SIZE - ENTITY_PADDING * 2.f,
                      ENTITY_SIZE - ENTITY_PADDING * 2.f),
        *EditorInput::instance);
  }

  // Decide on the arrow colours (for enabled / disabled)
  bool left_enabled = curr_page > 0;
  bool right_enabled =
      (curr_page + 1) * ENTITIES_PER_PAGE < entity_type_map.size();
  bool left_hovered = false;
  bool right_hovered = false;

  // Get left arrow / right arrow boxes
  Rect left_arrow_rect(rect.pos.x + 10.0, 
      rect.pos.y + rect.size.y / 2.f - 16.f, 30.f, 32.f);
  Rect right_arrow_rect(rect.pos.x + rect.size.x - 40.0, 
      rect.pos.y + rect.size.y / 2.f - 16.f, 30.f, 32.f);

  // Check mouse hover
  if (left_enabled) {
    if (left_arrow_rect.contains(input.mouse_pos)) {
      left_hovered = true;
    }
  }
  if (right_enabled) {
    if (right_arrow_rect.contains(input.mouse_pos)) {
      right_hovered = true;
    }
  }

  Color disabled(0.2f, 0.2f, 0.2f, 1.0f);
  Color hovered(2.2f, 2.2f, 0.0f, 1.0f);

  Color *lcol = left_enabled ? (left_hovered ? &hovered : &ui_fg) : &disabled;
  Color *rcol = right_enabled ? (right_hovered ? &hovered : &ui_fg) : &disabled;

  // Draw the backwards / forwards arrows
  Vertex tris[] = {
      Vertex(Vec2(left_arrow_rect.pos.x, 
            left_arrow_rect.pos.y + left_arrow_rect.size.y / 2.f), 
          lcol, Vec2(0.0, 0.0)),
      Vertex(Vec2(left_arrow_rect.pos.x + left_arrow_rect.size.x, 
            left_arrow_rect.pos.y), 
          lcol, Vec2(0.0, 0.0)),
      Vertex(Vec2(left_arrow_rect.pos.x + left_arrow_rect.size.x, 
            left_arrow_rect.pos.y + left_arrow_rect.size.y), 
          lcol, Vec2(0.0, 0.0)),

      Vertex(Vec2(right_arrow_rect.pos.x + right_arrow_rect.size.x, 
            right_arrow_rect.pos.y + right_arrow_rect.size.y / 2.f), 
          rcol, Vec2(0.0, 0.0)),
      Vertex(Vec2(right_arrow_rect.pos.x, 
            right_arrow_rect.pos.y), 
          rcol, Vec2(0.0, 0.0)),
      Vertex(Vec2(right_arrow_rect.pos.x, 
            right_arrow_rect.pos.y + right_arrow_rect.size.y), 
          rcol, Vec2(0.0, 0.0)),
  };
  pc->draw_tris_hud(tris, 2, pc->get_white_tex_handle());

  // Check if we've just clicked one of the arrows
  if (!input.lmb_down && input.lmb_down_prev) {
    if (left_hovered) {
      curr_page--;
    } else if (right_hovered) {
      curr_page++;
    }
  }
}
