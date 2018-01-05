#include "player_controlled.hpp"

CompPlayerControlled::CompPlayerControlled(EntityId entity_id,
                                           f32 force_to_apply) {
  this->entity_id = entity_id;
  this->force_to_apply = force_to_apply;
  this->state = 0;
}
