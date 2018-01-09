#pragma once
#include "comp/animation.hpp"
#include "comp/game_entity.hpp"
#include "comp/player_controlled.hpp"
#include "comp/wall.hpp"
#include "comp/tilemap.hpp"
#include "comp/ai_enemy_basic.hpp"
#include "comp/bullet.hpp"
#include "comp/sprite.hpp"
#include "engine/camera.hpp"
#include <chrono>
#include <cstdint>
#include <vector>

// Forward declaration or else circular include happens
class PaintSystem;
class UpdateSystem;
class InputState;
class PaintController;
class StandardTextures;

/************/
/** MACROS **/
/************/

/** Defining a macro for quickly generating functions to add components
 * # Usage
 * Given a component called 'CompPlayerControlled' which we would like to
 * generate functions like `add_comp_player_controlled(CompPlayerControlled
 * comp)` for, simply use the declare macro like so:
 *
 * ```
 * ECS_DECLARE_COMPONENT(CompPlayerControlled, player_controlled)
 * ```
 */
#define ECS_DECLARE_COMPONENT(TYPE, NAME)                                      \
private:                                                                       \
  std::vector<TYPE> comp_##NAME;                                               \
                                                                               \
public:                                                                        \
  void add_comp_##NAME(TYPE comp);

/** Macro for generating implementations of functions to add components. When
 * declaring a component of type `CompPlayerControlled`, with the name
 * `player_controlled`, use this macro in the implementation (.cpp) file as so:
 *
 * ```
 * ECS_IMPL_COMPONENT(CompPlayerControlled, player_controlled)
 * ```
 */
#define ECS_IMPL_COMPONENT(TYPE, NAME)                                         \
  void ECS::add_comp_##NAME(TYPE comp) { this->comp_##NAME.push_back(comp); }

/***********************/
/** Class declaration **/
/***********************/

/** Entity component system, containing lists of all the components. */
class ECS {
  /* The system class needs to access the components */
  friend class SystemPhysics;
  friend class SystemPlayerControlled;
  friend class SystemWallCollision;
  friend class SystemAnimationUpdate;
  friend class SystemGameEntityRenderer;
  friend class SystemWallRenderer;
  friend class SystemTilemapRenderer;
  friend class SystemPlayerEffectRenderer;
  friend class SystemAIEnemyBasic;
  friend class SystemBulletCollision;

  /* Auto generated component lists.. */
  ECS_DECLARE_COMPONENT(CompGameEntity, game_entity)
  ECS_DECLARE_COMPONENT(CompPlayerControlled, player_controlled)
  ECS_DECLARE_COMPONENT(CompWall, wall)
  ECS_DECLARE_COMPONENT(CompAnimation, animation)
  ECS_DECLARE_COMPONENT(CompSprite, sprite)
  ECS_DECLARE_COMPONENT(CompTilemap, tilemap)
  ECS_DECLARE_COMPONENT(CompAIEnemyBasic, ai_enemy_basic)
  ECS_DECLARE_COMPONENT(CompBullet, bullet)

private:
  std::vector<UpdateSystem *> update_systems;
  std::vector<PaintSystem *> paint_systems;
  int current_entity_id;

public:
  ECS();
  ~ECS();
  EntityId gen_entity_id();
  /** Updates the ECS */
  void update(InputState *input_state, Camera *camera, StandardTextures* std_tex);
  void paint(InputState *input_state, PaintController *paint_controller,
             Camera *camera, StandardTextures* std_tex);
};
