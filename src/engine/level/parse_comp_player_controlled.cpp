/**
 * This should only be included once from level.cpp.
 */

#include "engine/comp/player_controlled.hpp"
#include <json.hpp>

using namespace nlohmann;

void to_json(json& j, const CompPlayerControlled& c) {
  j = json();
}

void from_json(const json& j, CompPlayerControlled& c) {
}

