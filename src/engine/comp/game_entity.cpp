#include "engine/vec.hpp"
#include "game_entity.hpp"

CompGameEntity::CompGameEntity(EntityId entity_id, f32 mass, f32 damping) {
  this->entity_id = entity_id;
  this->mass = mass;
  this->damping= damping;
}
