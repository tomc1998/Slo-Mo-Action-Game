#pragma once
#include "engine/entity_id.hpp"
#include "engine/resource.hpp"
#include "engine/resource_manager.hpp"
#include <iostream>

class CompSprite {
public:
  CompSprite(EntityId entity_id, ResHandle th);

  EntityId entity_id;
  ResHandle th;
};
