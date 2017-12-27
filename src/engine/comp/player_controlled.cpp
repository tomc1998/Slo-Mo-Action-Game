#include "player_controlled.hpp"

CompPlayerControlled::CompPlayerControlled(f32 force_to_apply, EntityId entity_id) {
  this->force_to_apply = force_to_apply;
  this->entity_id = entity_id;
}
