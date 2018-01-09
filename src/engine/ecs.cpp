#include "comp/animation.hpp"
#include "comp/game_entity.hpp"
#include "comp/player_controlled.hpp"
#include "comp/tilemap.hpp"
#include "comp/wall.hpp"
#include "comp/bullet.hpp"
#include "comp/sprite.hpp"
#include "ecs.hpp"
#include "renderer/paint_controller.hpp"
#include "system/animation_update.cpp"
#include "system/game_entity_renderer.cpp"
#include "system/physics.cpp"
#include "system/player_controlled.cpp"
#include "system/wall_collision.cpp"
#include "system/wall_renderer.cpp"
#include "system/tilemap_renderer.cpp"
#include "system/player_effect_renderer.cpp"
#include "system/ai_enemy_basic.cpp"
#include "system/bullet_collision.cpp"

ECS_IMPL_COMPONENT(CompGameEntity, game_entity)
ECS_IMPL_COMPONENT(CompPlayerControlled, player_controlled)
ECS_IMPL_COMPONENT(CompWall, wall)
ECS_IMPL_COMPONENT(CompAnimation, animation)
ECS_IMPL_COMPONENT(CompSprite, sprite)
ECS_IMPL_COMPONENT(CompTilemap, tilemap)
ECS_IMPL_COMPONENT(CompAIEnemyBasic, ai_enemy_basic)
ECS_IMPL_COMPONENT(CompBullet, bullet)

ECS::ECS() {
  this->current_entity_id = 0;
  this->update_systems.push_back(new SystemPlayerControlled);
  this->update_systems.push_back(new SystemAIEnemyBasic);
  this->update_systems.push_back(new SystemPhysics);
  this->update_systems.push_back(new SystemWallCollision);
  this->update_systems.push_back(new SystemBulletCollision);
  this->update_systems.push_back(new SystemAnimationUpdate);

  this->paint_systems.push_back(new SystemTilemapRenderer);
  this->paint_systems.push_back(new SystemWallRenderer);
  this->paint_systems.push_back(new SystemGameEntityRenderer);
  this->paint_systems.push_back(new SystemPlayerEffectRenderer);
}

ECS::~ECS() {
  for (u32 ii = 0; ii < update_systems.size(); ii++) {
    delete update_systems[ii];
  }

  for (u32 ii = 0; ii < paint_systems.size(); ii++) {
    delete paint_systems[ii];
  }
}

EntityId ECS::gen_entity_id() {
  this->current_entity_id++;
  return this->current_entity_id;
}

void ECS::update(InputState *input_state, Camera *camera) {
  Globals g;
  g.ecs = this;
  g.input_state = input_state;
  g.paint_controller = NULL;
  g.camera = camera;
  for (u32 ii = 0; ii < this->update_systems.size(); ii++) {
    this->update_systems[ii]->handle_components(g);
  }
}

void ECS::paint(InputState *input_state, PaintController *paint_controller,
                Camera *camera) {
  Globals g;
  g.ecs = this;
  g.input_state = input_state;
  g.paint_controller = paint_controller;
  g.camera = camera;
  for (u32 ii = 0; ii < this->paint_systems.size(); ii++) {
    this->paint_systems[ii]->handle_components(g);
  }
}
