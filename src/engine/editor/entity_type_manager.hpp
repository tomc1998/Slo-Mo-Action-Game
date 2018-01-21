#pragma once

#include <sparsepp/spp.h>
#include "entity_type.hpp"

class Globals;

namespace CEGUI {
  class Window;
}

class EntityTypeManager {
private:
  spp::sparse_hash_map<std::string, EntityType> entity_type_map;

  /** UI detail - what page is the player currently viewing */
  u32 curr_page = 0;

public:
  void insert_entity_type(std::string name, EntityType type);
  void delete_entity_type(std::string name);
  EntityType get_entity_type(std::string name);
  /** Paint this entity type library to the screen */
  void paint(Globals &globals, FontHandle font);
  CEGUI::Window* create_library_window();
};
