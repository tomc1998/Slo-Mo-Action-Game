#include "test_screen.hpp"
#include "engine/screen.hpp"
#include "engine/comp/player_controlled.hpp"
#include "engine/comp/game_entity.hpp"
#include "engine/vec.hpp"
#include "engine/entity_id.hpp"

void TestScreen::init(ECS* ecs) {
  EntityId entity_id = ecs->gen_entity_id();
  ecs->add_comp_player_controlled(CompPlayerControlled(entity_id, 10.0f));
  ecs->add_comp_game_entity(CompGameEntity(entity_id, 10.0f, 0.2f));
}

TestScreen::~TestScreen() {
}
