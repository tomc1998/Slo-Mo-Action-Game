#pragma once
#include "engine/entity_id.hpp"
#include "engine/vec.hpp"

/**
 * A component for game entities (i.e. things which have an in-world position,
 * interact w/ physics, etc)
 */
class CompGameEntity {
public:
  /** Damping between 0 and 1 */
  CompGameEntity(EntityId entity_id, f32 mass, f32 damping);
  /** Damping between 0 and 1 */
  CompGameEntity(EntityId entity_id, Vec2 pos, f32 mass, f32 damping);

  EntityId entity_id;
  Vec2 pos = Vec2(0.0, 0.0);
  Vec2 vel = Vec2(0.0, 0.0);
  Vec2 acc = Vec2(0.0, 0.0);
  f32 rot;
  f32 mass;
  f32 damping;
};
