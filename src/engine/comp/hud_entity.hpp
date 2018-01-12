#pragma once
#include "engine/entity_id.hpp"
#include "engine/vec.hpp"
#include "engine/resource_defs.hpp"

// TODO: Rethink this class, not fully thought through and just used for testing
// really
class CompHudEntity {
public:
  CompHudEntity(EntityId entity_id, Vec2 pos, Vec2 size);
  EntityId entity_id;
  Vec2 pos;
  Vec2 size;
};
