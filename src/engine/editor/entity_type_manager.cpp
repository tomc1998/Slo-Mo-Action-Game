#include "engine/canvas_size.hpp"
#include "engine/color.hpp"
#include "engine/renderer/paint_controller.hpp"
#include "engine/resource_defs.hpp"
#include "engine/system/globals.hpp"
#include "entity_type_manager.hpp"
#include <iostream>
#include <iterator>
#include <utility>

void EntityTypeManager::insert_entity_type(std::string name, EntityType type) {
  entity_type_map[name] = type;
}

void EntityTypeManager::delete_entity_type(std::string name) {
  entity_type_map.erase(name);
}

EntityType EntityTypeManager::get_entity_type(std::string name) {
  return entity_type_map[name];
}

void EntityTypeManager::paint(Globals &globals, FontHandle font) {
  const auto pc = globals.paint_controller;
  static Color ui_bg(0.0f, 0.0f, 0.0f, 1.0f);
  static Color ui_fg(1.0f, 1.0f, 1.0f, 1.0f);
  const f32 PANEL_SIZE = 200.0f; // size of the bottom panel
  pc->fill_rect_hud(0.0, CANVAS_H - PANEL_SIZE, CANVAS_W, PANEL_SIZE, &ui_bg);
  // Split entities into pages
  const static f32 EDGE_PADDING = 40.0f;
  const static u32 ENTITIES_PER_PAGE = (CANVAS_W - EDGE_PADDING * 2.f) / 150.0f;
  const u32 entity_start_ix = curr_page * ENTITIES_PER_PAGE;
  auto begin = entity_type_map.begin();
  auto end = entity_type_map.end();
  if (entity_start_ix < entity_type_map.size()) {
    std::advance(begin, entity_start_ix);
    for (u32 ii = 0; ii < ENTITIES_PER_PAGE &&
                     ii + entity_start_ix < entity_type_map.size();
         ++ii) {
      auto &entity_type_pair = *begin;
      pc->draw_text_hud(entity_type_pair.first.c_str(),
                        EDGE_PADDING + (ii+1) * 150.0f + 75.0f, CANVAS_H - 40.0f,
                        TextAlign::BOT_CENTRE, font, &ui_fg);
      std::next(begin);
    }
  }
}
