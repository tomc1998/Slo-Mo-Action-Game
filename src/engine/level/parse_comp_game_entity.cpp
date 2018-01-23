/**
 * This should only be included once from level.cpp.
 */

#include "engine/comp/game_entity.hpp"
#include <json.hpp>

using namespace nlohmann;

void to_json(json& j, const CompGameEntity& c) {
  j = json{
    {"pos", c.pos}, 
    {"vel", c.vel}, 
    {"acc", c.acc}, 
    {"rot", c.rot}, 
    {"mass", c.mass}, 
    {"damping", c.damping}};
}

void from_json(const json& j, CompGameEntity& c) {
  c.pos = j["pos"].get<Vec2>();
  c.vel = j["vel"].get<Vec2>();
  c.acc = j["acc"].get<Vec2>();
  c.rot = j["rot"].get<f32>();
  c.mass = j["mass"].get<f32>();
  c.damping = j["damping"].get<f32>();
}
