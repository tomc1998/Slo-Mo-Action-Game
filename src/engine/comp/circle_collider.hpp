#pragma once

#include "engine/entity_id.hpp"

/** This is a more generic circle collider. Other components like bullets
 * define their own radii - this is to avoid the need to always join with a
 * circle collider, since we know a bullet will always want to collide with
 * stuff. */
class CompCircleCollider {
  public:
    CompCircleCollider();
    CompCircleCollider(EntityId entity_id);
    CompCircleCollider(EntityId entity_id, f32 rad);
    CompCircleCollider(EntityId entity_id, f32 rad, bool collides_with_walls);
    EntityId entity_id;
    f32 rad = 8.0f;
    bool collides_with_walls = true;
};
