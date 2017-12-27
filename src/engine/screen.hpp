#pragma once

#include "ecs.hpp"

class Screen {
public:
  /** Populate the given ECS with entities. */
  virtual void init(ECS *ecs) = 0;
  virtual ~Screen(){};
};
