/**
 * This should only be included once from level.cpp.
 */

#include "engine/comp/tilemap.hpp"
#include "engine/vec.hpp"
#include <json.hpp>
#include <vector>

using namespace nlohmann;

void to_json(json& j, const CompTilemap& c) {
  j = {
    {"pos", c.pos},
    {"tile_size", c.tile_size},
    {"w", c.w},
    {"h", c.h},
    {"tiles", c.tiles},
  };
}

void from_json(const json& j, CompTilemap& c) {
  c.pos = j["pos"];
  c.tile_size = j["tile_size"];
  c.w = j["w"];
  c.h = j["h"];
  c.tiles = j["tiles"].get<std::vector<u32> >();
}

