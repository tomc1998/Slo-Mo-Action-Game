#include "engine/canvas_size.hpp"
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

void EntityTypeManager::insert_entity_type(std::string name, EntityType type) {
  entity_type_map[name] = type;
  entity_widget_list.push_back(EntityWidget(&entity_type_map[name], &name));
}

void EntityTypeManager::delete_entity_type(std::string name) {
  entity_type_map.erase(name);
  for (u32 ii = 0; ii < entity_widget_list.size(); ++ii) {
    if (*entity_widget_list[ii].entity_name == name) {
      entity_widget_list.erase(entity_widget_list.begin() + ii);
      break;
    }
  }
}

EntityType EntityTypeManager::get_entity_type(std::string name) {
  return entity_type_map[name];
}

void EntityTypeManager::paint(Globals &globals, FontHandle font) {
  const auto pc = globals.paint_controller;
  static Color ui_bg(0.0f, 0.0f, 0.0f, 1.0f);
  static Color ui_fg(1.0f, 1.0f, 1.0f, 1.0f);
  const f32 PANEL_SIZE = 200.0f; // size of the bottom panel
  paint_panel(*pc, Rect(0.0, CANVAS_H - PANEL_SIZE, CANVAS_W, PANEL_SIZE));

  // Split entities into pages, then render the current page
  const static f32 HORI_PADDING = 60.0f;
  const static f32 VERT_PADDING = 40.0f;
  const static f32 ENTITY_PADDING = 5.0f;
  const static f32 ENTITY_SIZE = 150.0f;
  const static u32 ENTITIES_PER_PAGE =
      (CANVAS_W - HORI_PADDING * 2.f) / ENTITY_SIZE;
  const u32 entity_start_ix = curr_page * ENTITIES_PER_PAGE;
  for (u32 ii = entity_start_ix; ii < entity_start_ix + ENTITIES_PER_PAGE &&
                                 ii < entity_widget_list.size();
       ++ii) {
    entity_widget_list[ii].update_paint(
        *pc, Rect(HORI_PADDING + (ii-entity_start_ix)*ENTITY_SIZE + ENTITY_PADDING,
                  CANVAS_H - VERT_PADDING - ENTITY_SIZE + ENTITY_PADDING,
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

  // Check mouse hover
  if (left_enabled) {
    auto diff = globals.input_state->mouse_pos -
                Vec2(10.0f, CANVAS_H - PANEL_SIZE / 2.f - 16.f);
    if (diff.x < 30.f && diff.y < 32.f) {
      left_hovered = true;
    }
  }
  if (right_enabled) {
    auto diff = globals.input_state->mouse_pos -
                Vec2(CANVAS_W - 40.0f, CANVAS_H - PANEL_SIZE / 2.f - 16.f);
    if (diff.x > 0.0f && diff.x < 30.f && diff.y > 0.0f && diff.y < 32.f) {
      right_hovered = true;
    }
  }

  Color disabled(0.2f, 0.2f, 0.2f, 1.0f);
  Color hovered(2.2f, 2.2f, 0.0f, 1.0f);

  Color *lcol = left_enabled ? (left_hovered ? &hovered : &ui_fg) : &disabled;
  Color *rcol = right_enabled ? (right_hovered ? &hovered : &ui_fg) : &disabled;

  // Draw the backwards / forwards arrows
  Vertex tris[] = {
      Vertex(Vec2(20.0f, CANVAS_H - PANEL_SIZE / 2.f), lcol, Vec2(0.0, 0.0)),
      Vertex(Vec2(28.0f, CANVAS_H - PANEL_SIZE / 2.f - 8.0f), lcol,
             Vec2(0.0, 0.0)),
      Vertex(Vec2(28.0f, CANVAS_H - PANEL_SIZE / 2.f + 8.0f), lcol,
             Vec2(0.0, 0.0)),

      Vertex(Vec2(CANVAS_W - 20.0f, CANVAS_H - PANEL_SIZE / 2.f), rcol,
             Vec2(0.0, 0.0)),
      Vertex(Vec2(CANVAS_W - 28.0f, CANVAS_H - PANEL_SIZE / 2.f - 8.0f), rcol,
             Vec2(0.0, 0.0)),
      Vertex(Vec2(CANVAS_W - 28.0f, CANVAS_H - PANEL_SIZE / 2.f + 8.0f), rcol,
             Vec2(0.0, 0.0)),
  };
  pc->draw_tris_hud(tris, 2, pc->get_white_tex_handle());

  // Check if we've just clicked one of the arrows
  if (!globals.input_state->lmb_down && globals.input_state->lmb_down_prev) {
    if (left_hovered) {
      curr_page--;
    } else if (right_hovered) {
      curr_page++;
    }
  }
}
