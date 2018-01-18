#include "editor.hpp"
#include "engine/level/level.hpp"
#include "engine/vec.hpp"
#include <string>

void setup_entity_type_manager(EntityTypeManager &m) {
  EntityType e0;
  e0.game_entity = new CompGameEntity(0, Vec2(0.0, 0.0), 10.0, 0.2);
  m.insert_entity_type("Test Entity", e0);
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
#define X(TYPE, NAME) \
  ecs.comp_##NAME.clear(); \
  ecs.comp_##NAME.insert(ecs.comp_##NAME.begin(), \
      curr_level->ecs.comp_##NAME.begin(),\
      curr_level->ecs.comp_##NAME.end());
  RUN_X_MACRO_ON_ALL_COMPS
#undef X
  ecs.death_queue.clear();
  ecs.current_entity_id = 0;
}

void Editor::update_render(Globals& globals) {
  curr_level->ecs.paint(globals);

  // Render editor GUI
  entity_type_manager.paint(globals, font);
}
