#include "comp/game_entity.hpp"
#include "comp/player_controlled.hpp"
#include "ecs.hpp"
#include "renderer/paint_controller.hpp"
#include "system/debug_paint.cpp"
#include "system/physics.cpp"
#include "system/player_controlled.cpp"

ECS_IMPL_COMPONENT(CompGameEntity, game_entity)
ECS_IMPL_COMPONENT(CompPlayerControlled, player_controlled)

ECS::ECS() {
  this->current_entity_id = 0;
  this->update_systems.push_back(new SystemPlayerControlled);
  this->update_systems.push_back(new SystemPhysics);

  this->paint_systems.push_back(new SystemDebugPaint);
}

EntityId ECS::gen_entity_id() {
  this->current_entity_id++;
  return this->current_entity_id;
}

void ECS::update(InputState *input_state) {
  for (u32 ii = 0; ii < this->update_systems.size(); ii++) {
    this->update_systems[ii]->handle_components(this, input_state);
  }
}

void ECS::paint(InputState *input_state, PaintController paint_controller) {
  for (u32 ii = 0; ii < this->paint_systems.size(); ii++) {
    this->paint_systems[ii]->handle_components(this, input_state,
                                               paint_controller);
  }
}
