#include "engine/entity_id.hpp"
#include "engine/vec.hpp"
#include "wall.hpp"
#include <vector>

CompWall::CompWall(EntityId entity_id, std::vector<Vec2> vertices) {
  this->entity_id = entity_id;
  this->vertices = vertices;
}
