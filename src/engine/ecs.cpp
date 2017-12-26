#include "ecs.hpp"
#include "comp/game_entity.hpp"

ECS_IMPL_COMPONENT(CompGameEntity, game_entity)

void ECS::update() {
  for (u32 ii=0; ii < this->systems.size(); ii++) {
    this->systems[ii]->handle_components(this);
  }
}
