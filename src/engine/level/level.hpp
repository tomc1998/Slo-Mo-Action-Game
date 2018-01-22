#pragma once

#include "engine/ecs.hpp"
#include <string>

class ResourceManager;

class Level {
  friend class Editor;

private:
  /** An ECS for loading into the engine. */
  ECS ecs;
  Level();

public:
  /** Load a level from a given file */
  std::string name;
  Level(std::string path, ResourceManager& res_man);

  /** Given an ECS, load this level into it */
  void load_into_ecs(ECS& ecs);
};
