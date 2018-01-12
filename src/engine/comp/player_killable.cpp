#include "player_killable.hpp"

CompPlayerKillable::CompPlayerKillable(EntityId entity_id, u32 life_left) {
  this->entity_id = entity_id;
  this->life_left = life_left;
}

CompPlayerKillable::CompPlayerKillable(EntityId entity_id) {
  this->entity_id = entity_id;
}
