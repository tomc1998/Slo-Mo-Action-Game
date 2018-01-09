#include "bullet.hpp"

CompBullet::CompBullet(EntityId entity_id, f32 hit_rad) {
  this->entity_id = entity_id;
  this->hit_rad = hit_rad;
}

CompBullet::CompBullet() {}

