#include "editor.hpp"
#include "engine/level/level.hpp"
#include "engine/vec.hpp"
#include <string>

#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/OpenGL/GLRenderer.h>

void setup_cegui_res() {
  CEGUI::DefaultResourceProvider* rp = static_cast<CEGUI::DefaultResourceProvider*>
    (CEGUI::System::getSingleton().getResourceProvider());

  rp->setResourceGroupDirectory("imagesets", "assets/gui/imagesets/");
  rp->setResourceGroupDirectory("fonts", "assets/gui/fonts/");
  rp->setResourceGroupDirectory("layouts", "assets/gui/layouts/");
  rp->setResourceGroupDirectory("schemes", "assets/gui/schemes/");
  rp->setResourceGroupDirectory("looknfeel", "assets/gui/looknfeel/");

  CEGUI::ImageManager::setImagesetDefaultResourceGroup("imagesets");
  CEGUI::Font::setDefaultResourceGroup("fonts");
  CEGUI::Scheme::setDefaultResourceGroup("schemes");
  CEGUI::WindowManager::setDefaultResourceGroup("layouts");
  CEGUI::WidgetLookManager::setDefaultResourceGroup("looknfeel");
}

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

Editor::Editor(FontHandle font) : font(font), 
  gui_renderer(CEGUI::OpenGLRenderer::bootstrapSystem()) {
    curr_level = new Level();
    setup_entity_type_manager(entity_type_manager);

    // Setup editor gui
    using namespace CEGUI;
    setup_cegui_res();
    SchemeManager::getSingleton().createFromFile("TaharezLook.scheme");

    WindowManager& wmgr = WindowManager::getSingleton();
    root = wmgr.createWindow( "DefaultWindow", "root" );

    Window* entity_lib_win = entity_type_manager.create_library_window();
    root->addChild(entity_lib_win);

    System::getSingleton().getDefaultGUIContext().setRootWindow( root );
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
