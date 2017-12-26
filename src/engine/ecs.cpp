#include "ecs.hpp"
#include "comp/game_entity.hpp"

ECS_IMPL_COMPONENT(CompGameEntity, game_entity);

void ECS::update() {
  for (system=0; system < this->systems.size; system++) {
    this->systems[system].handle_components(this);
  }
}
