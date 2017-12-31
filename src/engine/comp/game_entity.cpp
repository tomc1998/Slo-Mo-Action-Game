#include "engine/vec.hpp"
#include "game_entity.hpp"

CompGameEntity::CompGameEntity(EntityId entity_id, f32 mass, f32 damping,
                               bool collides_with_walls) {
  this->entity_id = entity_id;
  this->mass = mass;
  this->damping = damping;
  this->collides_with_walls = collides_with_walls;
}
