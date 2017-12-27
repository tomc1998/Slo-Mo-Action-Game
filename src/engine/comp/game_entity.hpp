#pragma once
#include "engine/vec.hpp"
#include "engine/entity_id.hpp"

/**
 * A component for game entities (i.e. things which have an in-world position,
 * interact w/ physics, etc)
 */
class CompGameEntity {
  public:
    CompGameEntity(EntityId entity_id, f32 mass, Vec2 acc, Vec2 vel, Vec2 pos);
    EntityId entity_id;
    f32 mass;
    Vec2 acc;
    Vec2 vel;
    Vec2 pos;
};
