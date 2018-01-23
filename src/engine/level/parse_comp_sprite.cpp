/**
 * This should only be included once from level.cpp.
 */

#include "engine/comp/sprite.hpp"
#include <json.hpp>

using namespace nlohmann;

void to_json(json& j, const CompSprite& c) {
  j = json();
}

void from_json(const json& j, CompSprite& c) {
}


