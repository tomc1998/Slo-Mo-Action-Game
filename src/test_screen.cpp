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
#include "engine/level/level.hpp"
#include <sparsepp/spp.h>
#include <iostream>
#include <vector>

void TestScreen::init(ECS *ecs, ResourceManager *res_manager) {
  Level level("assets/levels/test_level.json", *res_manager);
  level.load_into_ecs(*ecs);
}

TestScreen::~TestScreen() {}
