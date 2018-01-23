/**
 * This should only be included once from level.cpp.
 */

#include "engine/comp/animation.hpp"
#include <json.hpp>

using namespace nlohmann;

void to_json(json& j, const CompAnimation& c) {
  j = json();
}

void from_json(const json& j, CompAnimation& c) {
}



