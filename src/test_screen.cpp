#include "test_screen.hpp"
#include "engine/screen.hpp"
#include "engine/comp/player_controlled.hpp"
#include "engine/comp/game_entity.hpp"
#include "engine/vec.hpp"

void TestScreen::init(ECS* ecs) {
  EntityId entity_id = ecs->gen_entity_id();
  ecs->add_comp_player_controlled(CompPlayerControlled(10.0f, entity_id));
  ecs->add_comp_game_entity(CompGameEntity(1.0f, Vec2(0.0f, 0.0f), Vec2(0.0f, 0.0f), Vec2(300.0f, 300.0f), entity_id));



} 

TestScreen::~TestScreen() {
}
