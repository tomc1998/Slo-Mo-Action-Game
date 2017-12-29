#pragma once

#include "ecs.hpp"

class Screen {
public:
  /** Populate the given ECS with entities. */
  virtual void init(ECS *ecs, ResourceManager *res_manager) = 0;
  virtual ~Screen(){};
};
