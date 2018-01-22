#include "player_controlled.hpp"

CompPlayerControlled::CompPlayerControlled() {
  this->force_to_apply = 600.0f;
  this->state = 0;
  this->state_change_timer = 0;
}

CompPlayerControlled::CompPlayerControlled(EntityId entity_id,
                                           f32 force_to_apply) {
  this->entity_id = entity_id;
  this->force_to_apply = force_to_apply;
  this->state = 0;
  this->state_change_timer = 0;
}

void CompPlayerControlled::set_state(u8 state) {
  this->state = state;
  state_change_timer = 0;
}

u8 CompPlayerControlled::get_state() { return state; }
