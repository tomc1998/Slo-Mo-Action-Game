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
  const static f32 HORI_PADDING = 25.0f;
  const static f32 VERT_PADDING = 25.0f;
  const static f32 ENTITY_PADDING = 5.0f;
  const static f32 ENTITY_SIZE = 150.0f;
  const static u32 ENTITIES_PER_PAGE =
      (CANVAS_W - HORI_PADDING * 2.f) / ENTITY_SIZE;
  const u32 entity_start_ix = curr_page * ENTITIES_PER_PAGE;
  auto begin = entity_type_map.begin();
  if (entity_start_ix < entity_type_map.size()) {
    std::advance(begin, entity_start_ix);
    for (u32 ii = 0; ii < ENTITIES_PER_PAGE &&
                     ii + entity_start_ix < entity_type_map.size();
         ++ii) {
      auto &entity_type_pair = *begin;
      pc->fill_rect_hud(HORI_PADDING + (ii)*ENTITY_SIZE + ENTITY_PADDING,
                        CANVAS_H - VERT_PADDING - ENTITY_SIZE + ENTITY_PADDING,
                        ENTITY_SIZE - ENTITY_PADDING * 2.f,
                        ENTITY_SIZE - ENTITY_PADDING * 2.f, &ui_fg);
      pc->fill_rect_hud(HORI_PADDING + (ii)*ENTITY_SIZE + ENTITY_PADDING + 1.5f,
                        CANVAS_H - VERT_PADDING + 1.5f - ENTITY_SIZE +
                            ENTITY_PADDING,
                        ENTITY_SIZE - 3.f - ENTITY_PADDING * 2.f,
                        ENTITY_SIZE - 3.f - ENTITY_PADDING * 2.f, &ui_bg);
      pc->draw_text_hud(entity_type_pair.first.c_str(),
                        HORI_PADDING + (ii)*ENTITY_SIZE + ENTITY_SIZE / 2.f,
                        CANVAS_H - VERT_PADDING/2.f, TextAlign::BOT_CENTRE, font,
                        &ui_fg);
      begin ++;
    }
  }
}
