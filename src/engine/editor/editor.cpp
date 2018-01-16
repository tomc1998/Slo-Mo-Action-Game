#include "editor.hpp"
#include "engine/level/level.hpp"

Editor::Editor() {
  curr_level = new Level();
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
}
