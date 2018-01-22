/**
 * This should only be included once from level.cpp.
 */

#include "engine/comp/player_killable.hpp"
#include <json.hpp>

using namespace nlohmann;

void to_json(json& j, const CompPlayerKillable& c) {
  j = json{ {"life", c.life_left} };
}

void from_json(const json& j, CompPlayerKillable& c) {
  c.life_left = j["life"];
}

