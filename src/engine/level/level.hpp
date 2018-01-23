#pragma once

#include "engine/ecs.hpp"
#include "engine/entity_id.hpp"
#include <string>

class ResourceManager;

class Level {
  friend class Editor;

private:
  /** An ECS for loading into the engine. */
  ECS ecs;
  /** A map of names to entities, useful for editing. Never actually loaded
   * into the game when calling load_into_ecs, so no major in-game performance
   * impact. */
  spp::sparse_hash_map<std::string, EntityId> entity_name_id_map;
  Level();

public:
  /** Load a level from a given file */
  std::string name;
  Level(std::string path, ResourceManager &res_man);

  /** Given an ECS, load this level into it */
  void load_into_ecs(ECS &ecs);
};
