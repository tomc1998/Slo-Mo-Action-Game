#pragma once

#include "engine/entity_id.hpp"

class CompCircleCollider {
  public:
    CompCircleCollider(EntityId entity_id);
    CompCircleCollider(EntityId entity_id, f32 rad);
    CompCircleCollider(EntityId entity_id, f32 rad, bool collides_with_walls);
    EntityId entity_id;
    f32 rad = 8.0f;
    bool collides_with_walls = true;
};
