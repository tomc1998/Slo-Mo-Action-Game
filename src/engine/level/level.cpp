#include "level.hpp"
#include <fstream>
#include <iostream>
#include <json.hpp>

#include "engine/ecs.hpp"
#include "engine/entity_id.hpp"
#include "parse_comp_game_entity.cpp"
#include "parse_comp_player_controlled.cpp"
#include "parse_comp_tilemap.cpp"
#include "parse_comp_wall.cpp"
#include "parse_comp_animation.cpp"
#include "parse_comp_sprite.cpp"
#include "parse_comp_circle_collider.cpp"
#include "parse_comp_player_killable.cpp"
#include "parse_comp_ai_enemy_basic.cpp"
#include "parse_comp_waypoint_graph.cpp"
#include "parse_resources.cpp"

Level::Level() {}

// Doesn't include the components which need extra resource linkage, like
// 'sprite' or 'animation'.
#define RUN_X_MACRO_ON_ALL_PARSEABLE_COMPS                                     \
  X(CompGameEntity, game_entity)                                               \
  X(CompPlayerControlled, player_controlled)                                   \
  X(CompAIEnemyBasic, ai_enemy_basic)                                          \
  X(CompPlayerKillable, player_killable)                                       \
  X(CompCircleCollider, circle_collider)                                       \
  X(CompWaypointGraph, waypoint_graph)

void Level::load_into_ecs(ECS& _ecs) {
#define X(TYPE, NAME) \
  _ecs.comp_##NAME.clear(); \
  _ecs.comp_##NAME.insert(_ecs.comp_##NAME.begin(), \
      ecs.comp_##NAME.begin(),\
      ecs.comp_##NAME.end());
  RUN_X_MACRO_ON_ALL_COMPS
#undef X
  _ecs.death_queue.clear();
  _ecs.current_entity_id = ecs.current_entity_id;
}

Level::Level(std::string path, ResourceManager &res_man) {
  using namespace nlohmann;
  std::ifstream i(path);
  json j;
  i >> j;

  this->name = j["name"].get<std::string>();

  // Parse resources
  auto res_map = parse_resources(j["resources"], res_man);

  // Parse entities
  const json &entities = j["entities"];
  for (const auto &e : entities) {
    EntityId e_id = ecs.gen_entity_id();
    std::string name = e["name"];
    entity_name_id_map[name] = e_id;
    for (auto it = e.cbegin(); it != e.cend(); ++it) {
      std::string comp_name = it.key();
      json c = it.value();

#define X(TYPE, NAME)                                                          \
  if (comp_name == "comp_"#NAME) {                                            \
    TYPE component = c.get<TYPE>();                                            \
    component.entity_id = e_id;                                                \
    ecs.add_comp_##NAME(component);                                            \
  }
        RUN_X_MACRO_ON_ALL_PARSEABLE_COMPS
#undef X

      // Perform linking up of resources which can't be generated
      if (comp_name == "comp_sprite") {
        ecs.add_comp_sprite(CompSprite(e_id, res_map[c["sprite"]]));
      } else if (comp_name == "comp_animation") {
        ecs.add_comp_animation(CompAnimation(e_id, res_map[c["animation"]], 400));
      }
      else if (comp_name == "comp_tilemap") {
        CompTilemap component = c.get<CompTilemap>();
        component.entity_id = e_id;
        component.tileset = res_map[c["tileset"]];
        ecs.add_comp_tilemap(component);
      }
      else if (comp_name == "comp_wall") {
        CompWall component = c.get<CompWall>();
        component.entity_id = e_id;
        component.edge_tex = res_map[c["edge_tex"]];
        ecs.add_comp_wall(component);
      }
    }
  }
}
