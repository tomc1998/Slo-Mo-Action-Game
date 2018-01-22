/**
 * This should only be included once from level.cpp.
 */

#include "engine/comp/wall.hpp"
#include <json.hpp>
#include <stdexcept>
#include <vector>

using namespace nlohmann;

void to_json(json& j, const CompWall& c) {
  throw std::runtime_error("Can't yet serialise wall to file - need to be able to get edge tex!");
}

void from_json(const json& j, CompWall& c) {
  c.vertices = j["vertices"].get<std::vector<Vec2> >();
}

