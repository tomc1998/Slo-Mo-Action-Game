#pragma once

#include <sparsepp/spp.h>
#include "entity_type.hpp"

class EntityTypeManager {
private:
  spp::sparse_hash_map<std::string, EntityType> entity_type_map;

public:
  void insert_entity_type(std::string name, EntityType type);
  void delete_entity_type(std::string name);
  EntityType get_entity_type(std::string name);
};
