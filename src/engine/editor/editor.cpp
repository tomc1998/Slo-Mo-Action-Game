#include "editor.hpp"
#include "engine/canvas_size.hpp"
#include "engine/level/level.hpp"
#include "engine/vec.hpp"
#include "input.hpp"
#include "engine/system/globals.hpp"
#include <string>

void setup_entity_type_manager(EntityTypeManager &m) {
  EntityType e0;
  e0.game_entity = new CompGameEntity(0, Vec2(0.0, 0.0), 10.0, 0.2);
  m.insert_entity_type(std::string("0"), e0);
  m.insert_entity_type(std::string("1"), e0);
  m.insert_entity_type(std::string("2"), e0);
  m.insert_entity_type(std::string("3"), e0);
  m.insert_entity_type(std::string("4"), e0);
  m.insert_entity_type(std::string("5"), e0);
  m.insert_entity_type(std::string("6"), e0);
  m.insert_entity_type(std::string("7"), e0);
  m.insert_entity_type(std::string("8"), e0);
  m.insert_entity_type(std::string("9"), e0);
  m.insert_entity_type(std::string("10"), e0);
}

Editor::Editor(FontHandle font) : font(font) {
  curr_level = new Level();
  setup_entity_type_manager(entity_type_manager);
}

Editor::~Editor() {
  delete curr_level;
}

void Editor::new_level() {
  delete curr_level;
  curr_level = new Level();
}

void Editor::load_curr_level_into_ecs(ECS& ecs) const {
  curr_level->load_into_ecs(ecs);
}

void Editor::update_render(Globals& globals) {
  // Draw the level
  curr_level->ecs.paint(globals);

  // Handle input
  if (EditorInput::instance->toggle_library_just_pressed()) {
    library_visible = !library_visible;
  }

  // Create a gui context for rendering GUI widgets
  GuiContext c(font, globals.paint_controller);

  // Render editor GUI
  if (library_visible) { 
    entity_type_manager.paint(c, 
        Rect(0.0, CANVAS_H - 200.0f, CANVAS_W, 200.0f), 
        *EditorInput::instance);
  }
}

