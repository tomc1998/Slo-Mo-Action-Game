#include "engine/vec.hpp"
#include "game_entity.hpp"

CompGameEntity::CompGameEntity(EntityId entity_id, f32 mass, f32 damping, Vec2 acc, Vec2 vel, Vec2 pos) {
  this->entity_id = entity_id;
  this->mass = mass;
  this->damping= damping;
  this->acc = acc;
  this->vel = vel;
  this->pos = pos;
    
}
