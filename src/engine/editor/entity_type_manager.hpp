#pragma once

#include <sparsepp/spp.h>
#include "entity_type.hpp"
#include "gui/gui.hpp"

class Globals;

class EntityTypeManager {
private:
  spp::sparse_hash_map<std::string, EntityType> entity_type_map;
  std::vector<EntityWidget> entity_widget_list;

  /** UI detail - what page is the player currently viewing */
  u32 curr_page = 0;

public:
  void insert_entity_type(std::string name, EntityType type);
  void delete_entity_type(std::string name);
  EntityType get_entity_type(std::string name);
  /** Paint this entity type library to the screen */
  void paint(Globals &globals, FontHandle font);
};
