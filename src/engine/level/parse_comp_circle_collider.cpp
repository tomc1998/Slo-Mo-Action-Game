/**
 * This should only be included once from level.cpp.
 */

#include "engine/comp/circle_collider.hpp"
#include <json.hpp>
#include <stdexcept>
#include <vector>

using namespace nlohmann;

void to_json(json& j, const CompCircleCollider& c) {
  j = {
    {"rad", c.rad},
    {"collides_with_walls", c.collides_with_walls},
  };
}

void from_json(const json& j, CompCircleCollider& c) {
  c.rad = j["rad"].get<f32>();
  c.collides_with_walls = j["collides_with_walls"].get<bool>();
}


