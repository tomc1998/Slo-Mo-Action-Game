#pragma once

#include "engine/entity_id.hpp"

class CompBullet {
  public:
    CompBullet(EntityId entity_id, f32 hit_rad);
    CompBullet();
    EntityId entity_id = -1;
    /** Hitbox radius */
    f32 hit_rad = 0.0f;
};
