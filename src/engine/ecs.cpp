#include "comp/animation.hpp"
#include "comp/bullet.hpp"
#include "comp/game_entity.hpp"
#include "comp/player_controlled.hpp"
#include "comp/player_killable.hpp"
#include "comp/sprite.hpp"
#include "comp/tilemap.hpp"
#include "comp/wall.hpp"
#include "comp/circle_collider.hpp"
#include "ecs.hpp"
#include "renderer/paint_controller.hpp"
#include "system/ai_enemy_basic.cpp"
#include "system/animation_update.cpp"
#include "system/bullet_collision.cpp"
#include "system/check_death.cpp"
#include "system/game_entity_renderer.cpp"
#include "system/globals.hpp"
#include "system/physics.cpp"
#include "system/player_controlled.cpp"
#include "system/player_effect_renderer.cpp"
#include "system/tilemap_renderer.cpp"
#include "system/wall_collision.cpp"
#include "system/wall_renderer.cpp"

template <class T> T *ECS::find_id(T *comp_list, u32 len, EntityId target_id) {
  u32 min = 0;
  u32 max = len;
  u32 ii;

  while (min < max) {
    ii = min + (max - min) / 2;
    if (comp_list[ii].entity_id == target_id) {
      return &comp_list[ii];
    }

    if (comp_list[ii].entity_id < target_id) {
      min = ii + 1;
    }

    else {
      max = ii;
    }
  }

  return NULL;
}

ECS_IMPL_COMPONENT(CompGameEntity, game_entity)
ECS_IMPL_COMPONENT(CompPlayerControlled, player_controlled)
ECS_IMPL_COMPONENT(CompWall, wall)
ECS_IMPL_COMPONENT(CompAnimation, animation)
ECS_IMPL_COMPONENT(CompSprite, sprite)
ECS_IMPL_COMPONENT(CompTilemap, tilemap)
ECS_IMPL_COMPONENT(CompAIEnemyBasic, ai_enemy_basic)
ECS_IMPL_COMPONENT(CompBullet, bullet)
ECS_IMPL_COMPONENT(CompPlayerKillable, player_killable)
ECS_IMPL_COMPONENT(CompCircleCollider, circle_collider)

ECS::ECS() {
  this->current_entity_id = 0;
  this->update_systems.push_back(new SystemPlayerControlled);
  this->update_systems.push_back(new SystemAIEnemyBasic);
  this->update_systems.push_back(new SystemPhysics);
  this->update_systems.push_back(new SystemWallCollision);
  this->update_systems.push_back(new SystemBulletCollision);
  this->update_systems.push_back(new SystemAnimationUpdate);
  this->update_systems.push_back(new SystemCheckDeath);

  this->paint_systems.push_back(new SystemTilemapRenderer);
  this->paint_systems.push_back(new SystemWallRenderer);
  this->paint_systems.push_back(new SystemGameEntityRenderer);
  this->paint_systems.push_back(new SystemPlayerEffectRenderer);

  death_queue.reserve(64);
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

void ECS::update(InputState *input_state, Camera *camera,
                 StandardTextures *std_tex) {
  Globals g;
  g.ecs = this;
  g.input_state = input_state;
  g.paint_controller = NULL;
  g.camera = camera;
  g.std_tex = std_tex;
  for (u32 ii = 0; ii < this->update_systems.size(); ii++) {
    this->update_systems[ii]->handle_components(g);
  }
  kill_entities();
}

void ECS::paint(InputState *input_state, PaintController *paint_controller,
                Camera *camera, StandardTextures *std_tex) {
  Globals g;
  g.ecs = this;
  g.input_state = input_state;
  g.paint_controller = paint_controller;
  g.camera = camera;
  g.std_tex = std_tex;
  for (u32 ii = 0; ii < this->paint_systems.size(); ii++) {
    this->paint_systems[ii]->handle_components(g);
  }
}

void ECS::queue_entity_death(EntityId entity_id) {
  death_queue.push_back(entity_id);
}

void ECS::kill_entities() {
#define ERASE_COMP(NAME, ID)                                                   \
  {                                                                            \
    const auto loc = find_comp_##NAME##_with_id(ID);                           \
    if (loc != NULL) {                                                         \
      const auto ix = (u32)(loc - &comp_##NAME[0]);                            \
      comp_##NAME.erase(comp_##NAME.begin() + ix);                             \
    }                                                                          \
  }

  for (const auto id : death_queue) {
    ERASE_COMP(game_entity, id)
    ERASE_COMP(player_controlled, id)
    ERASE_COMP(wall, id)
    ERASE_COMP(animation, id)
    ERASE_COMP(sprite, id)
    ERASE_COMP(tilemap, id)
    ERASE_COMP(ai_enemy_basic, id)
    ERASE_COMP(bullet, id)
    ERASE_COMP(player_killable, id)
    ERASE_COMP(circle_collider, id)
  }

#undef ERASE_COMP
  death_queue.clear();
}
