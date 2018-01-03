#include "engine/comp/animation.hpp"
#include "engine/comp/game_entity.hpp"
#include "engine/comp/player_controlled.hpp"
#include "engine/comp/wall.hpp"
#include "engine/entity_id.hpp"
#include "engine/animation.hpp"
#include "engine/texture.hpp"
#include "engine/screen.hpp"
#include "engine/vec.hpp"
#include "test_screen.hpp"
#include "engine/resource_manager.hpp"
#include "engine/texture.hpp"
#include "engine/resource_defs.hpp"
#include <vector>

void TestScreen::init(ECS *ecs, ResourceManager *res_manager) {
  EntityId entity_id = ecs->gen_entity_id();
  ecs->add_comp_player_controlled(CompPlayerControlled(entity_id, 600.0f));
  ecs->add_comp_game_entity(CompGameEntity(entity_id, 10.0f, 0.02f, true));


  TexHandle player = res_manager->load_texture("assets/sprites/player.png");
  TexHandle foot = res_manager->load_texture("assets/sprites/foot.png");
  std::vector<TexHandle> texs;
  texs.push_back(foot);
  texs.push_back(foot);
  texs.push_back(player);

  AnimHandle ah = res_manager->load_animation("assets/animations/walk.json", texs);
  ecs->add_comp_animation(CompAnimation(entity_id, ah, 400));

  TexHandle wall_tex = res_manager->load_texture("assets/sprites/test_wall.png");
  EntityId wall_id = ecs->gen_entity_id();

  std::vector<Vec2> vertices;
  vertices.push_back(Vec2(120.0f, 100.0f));
  vertices.push_back(Vec2(200.0f, 100.0f));
  vertices.push_back(Vec2(220.0f, 200.0f));
  vertices.push_back(Vec2(80.0f, 200.0f));

  ecs->add_comp_wall(CompWall(wall_id, vertices, wall_tex));
}

TestScreen::~TestScreen() {}
