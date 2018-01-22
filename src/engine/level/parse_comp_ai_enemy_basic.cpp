/**
 * This should only be included once from level.cpp.
 */

#include "engine/comp/ai_enemy_basic.hpp"
#include <json.hpp>

using namespace nlohmann;

void to_json(json& j, const CompAIEnemyBasic& c) {
  j = json();
}

void from_json(const json& j, CompAIEnemyBasic& c) {
}


