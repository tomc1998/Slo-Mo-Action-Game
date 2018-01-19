#include "editor.hpp"
#include "engine/level/level.hpp"
#include "engine/vec.hpp"
#include <string>

#define CEGUI_USE_GLEW
#include <CEGUI/RendererModules/OpenGL/GL3Renderer.h>

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
  CEGUI::OpenGL3Renderer& myRenderer =
      CEGUI::OpenGL3Renderer::bootstrapSystem();
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
