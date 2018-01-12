#include "engine/vec.hpp"
#include "engine/entity_id.hpp"
#include "game_entity.hpp"

CompGameEntity::CompGameEntity(EntityId entity_id, f32 mass, f32 damping) {
  this->entity_id = entity_id;
  this->mass = mass;
  this->damping = damping;
  this->rot = 0.0f;
}

CompGameEntity::CompGameEntity(EntityId entity_id, Vec2 pos, f32 mass, f32 damping) {
  this->entity_id = entity_id;
  this->mass = mass;
  this->damping = damping;
  this->pos = pos;
  this->rot = 0.0f;
}
