#include "circle_collider.hpp"

CompCircleCollider::CompCircleCollider() {}
CompCircleCollider::CompCircleCollider(EntityId entity_id)
    : entity_id(entity_id) {}
CompCircleCollider::CompCircleCollider(EntityId entity_id, f32 rad)
    : entity_id(entity_id), rad(rad) {}
CompCircleCollider::CompCircleCollider(EntityId entity_id, f32 rad, bool collides_with_walls)
    : entity_id(entity_id), rad(rad), collides_with_walls(collides_with_walls) {}
