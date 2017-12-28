#pragma once
#include "engine/entity_id.hpp"
#include "engine/vec.hpp"
#include <vector>

/**
 * A component which consists of a vector of vertices creating a polygonal wall
 */

class CompWall {
public:
  CompWall(EntityId entity_id, std::vector<Vec2> vertices);

  EntityId entity_id;
  std::vector<Vec2> vertices;
};
