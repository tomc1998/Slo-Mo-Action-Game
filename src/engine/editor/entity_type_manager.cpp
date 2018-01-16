#include "entity_type_manager.hpp"

void EntityTypeManager::insert_entity_type(std::string name,
                                           EntityType type) {
  entity_type_map[name] = type;
}

void EntityTypeManager::delete_entity_type(std::string name) {
  entity_type_map.erase(name);
}

EntityType EntityTypeManager::get_entity_type(std::string name) {
  return entity_type_map[name];
}
