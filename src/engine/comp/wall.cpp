#include "engine/entity_id.hpp"
#include "engine/vec.hpp"
#include "wall.hpp"
#include <vector>

CompWall::CompWall(EntityId entity_id, std::vector<Vec2> vertices, TexHandle edge_tex)
    : entity_id(entity_id), vertices(vertices), edge_tex(edge_tex) {}
