#include "player_killable.hpp"

CompPlayerKillable::CompPlayerKillable(EntityId entity_id, float hit_rad, u32 life_left) {
  this->entity_id = entity_id;
  this->hit_rad = hit_rad;
  this->life_left = life_left;
}

CompPlayerKillable::CompPlayerKillable(EntityId entity_id) {
  this->entity_id = entity_id;
}
