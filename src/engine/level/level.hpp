#pragma once

#include "engine/ecs.hpp"

class Level {
  friend class Editor;

  private:
  /** An ECS for loading into the engine. */
  ECS ecs;
};
