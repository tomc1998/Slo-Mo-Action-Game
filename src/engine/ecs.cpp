#include "ecs.hpp"
#include "comp/game_entity.hpp"
#include "comp/player_controlled.hpp"
#include "system/physics.cpp"
#include "system/player_controlled.cpp"

ECS_IMPL_COMPONENT(CompGameEntity, game_entity)
ECS_IMPL_COMPONENT(CompPlayerControlled, player_controlled)

ECS::ECS() {
  this->current_entity_id = 0;
  this->systems.push_back(new SystemPlayerControlled);
  this->systems.push_back(new SystemPhysics);

}

EntityId ECS::gen_entity_id() {
  this->current_entity_id++;
  return this->current_entity_id;
}

void ECS::update(InputState* input_state) {
  for (u32 ii=0; ii < this->systems.size(); ii++) {
    this->systems[ii]->handle_components(this, input_state);
  }
}


