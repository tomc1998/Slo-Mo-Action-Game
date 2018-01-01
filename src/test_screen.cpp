#include "engine/comp/animation.hpp"
#include "engine/comp/game_entity.hpp"
#include "engine/comp/player_controlled.hpp"
#include "engine/comp/wall.hpp"
#include "engine/entity_id.hpp"
#include "engine/animation.hpp"
#include "engine/texture.hpp"
#include "engine/resource_manager.hpp"
#include "engine/screen.hpp"
#include "engine/vec.hpp"
#include "test_screen.hpp"
#include <iostream>
#include <vector>


void TestScreen::init(ECS *ecs, ResourceManager *res_manager) {
  EntityId entity_id = ecs->gen_entity_id();
  ecs->add_comp_player_controlled(CompPlayerControlled(entity_id, 600.0f));
  ecs->add_comp_game_entity(CompGameEntity(entity_id, 10.0f, 0.02f, true));
  AnimHandle ah = res_manager->load_test_animation();
  ecs->add_comp_animation(CompAnimation(entity_id, ah, 1000));

  EntityId wall_id = ecs->gen_entity_id();

  std::vector<Vec2> vertices;
  vertices.push_back(Vec2(100.0f, 100.0f));
  vertices.push_back(Vec2(150.0f, 100.0f));
  vertices.push_back(Vec2(200.0f, 200.0f));
  vertices.push_back(Vec2(100.0f, 200.0f));

  ecs->add_comp_wall(CompWall(wall_id, vertices));
}

TestScreen::~TestScreen() {}
