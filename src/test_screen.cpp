#include "engine/animation.hpp"
#include "engine/comp/animation.hpp"
#include "engine/comp/game_entity.hpp"
#include "engine/comp/player_controlled.hpp"
#include "engine/comp/wall.hpp"
#include "engine/entity_id.hpp"
#include "engine/resource_defs.hpp"
#include "engine/resource_manager.hpp"
#include "engine/screen.hpp"
#include "engine/texture.hpp"
#include "engine/texture.hpp"
#include "engine/vec.hpp"
#include "test_screen.hpp"
#include <vector>

void TestScreen::init(ECS *ecs, ResourceManager *res_manager) {
  // Add player
  EntityId entity_id = ecs->gen_entity_id();
  ecs->add_comp_player_controlled(CompPlayerControlled(entity_id, 600.0f));
  ecs->add_comp_game_entity(CompGameEntity(entity_id, 10.0f, 0.02f, true));

  TexHandle player = res_manager->load_texture("assets/sprites/player.png");
  TexHandle foot = res_manager->load_texture("assets/sprites/foot.png");
  std::vector<TexHandle> texs;
  texs.push_back(foot);
  texs.push_back(foot);
  texs.push_back(player);

  AnimHandle ah =
      res_manager->load_animation("assets/animations/walk.json", texs);
  ecs->add_comp_animation(CompAnimation(entity_id, ah, 400));

  // Add enemy
  EntityId enemy_id = ecs->gen_entity_id();
  ecs->add_comp_animation(CompAnimation(enemy_id, ah, 200));
  ecs->add_comp_game_entity(CompGameEntity(enemy_id, 10.0f, 0.02f, true));
  ecs->add_comp_ai_enemy_basic(CompAIEnemyBasic(enemy_id));
  ecs->add_comp_player_killable(CompPlayerKillable(enemy_id));

  // Add wall
  TexHandle wall_tex =
      res_manager->load_texture("assets/sprites/test_wall.png");
  EntityId wall_id = ecs->gen_entity_id();

  std::vector<Vec2> vertices;
  vertices.push_back(Vec2(120.0f, 100.0f));
  vertices.push_back(Vec2(200.0f, 100.0f));
  vertices.push_back(Vec2(220.0f, 200.0f));
  vertices.push_back(Vec2(80.0f, 200.0f));

  ecs->add_comp_wall(CompWall(wall_id, vertices, wall_tex));

  // Add tilemap
  TilesetHandle tileset = res_manager->load_tileset(
      "assets/sprites/tilesets/grass_test.png", 4, 4);

  u32 tiles[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
  CompTilemap tilemap(ecs->gen_entity_id(), tileset, Vec2(-100.0, -100.0), 4, 4,
                      Vec2(16.0, 16.0), tiles);
  ecs->add_comp_tilemap(tilemap);
}

TestScreen::~TestScreen() {}
