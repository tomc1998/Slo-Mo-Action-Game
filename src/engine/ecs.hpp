#pragma once
#include "comp/ai_enemy_basic.hpp"
#include "comp/animation.hpp"
#include "comp/bullet.hpp"
#include "comp/game_entity.hpp"
#include "comp/player_controlled.hpp"
#include "comp/sprite.hpp"
#include "comp/tilemap.hpp"
#include "comp/player_killable.hpp"
#include "comp/wall.hpp"
#include "comp/hud_entity.hpp"
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
  void add_comp_##NAME(TYPE comp);                                             \
  TYPE *find_comp_##NAME##_with_id(EntityId entity_id);

/** Macro for generating implementations of functions to add components. When
 * declaring a component of type `CompPlayerControlled`, with the name
 * `player_controlled`, use this macro in the implementation (.cpp) file as so:
 *
 * ```
 * ECS_IMPL_COMPONENT(CompPlayerControlled, player_controlled)
 * ```
 */
#define ECS_IMPL_COMPONENT(TYPE, NAME)                                         \
  void ECS::add_comp_##NAME(TYPE comp) { this->comp_##NAME.push_back(comp); }  \
  TYPE *ECS::find_comp_##NAME##_with_id(EntityId entity_id) {                       \
    return ECS::find_id<TYPE>(&comp_##NAME[0], comp_##NAME.size(), entity_id);            \
  }

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
  friend class SystemCheckDeath;
  friend class SystemHudRenderer;

  /* Auto generated component lists.. */
  ECS_DECLARE_COMPONENT(CompGameEntity, game_entity)
  ECS_DECLARE_COMPONENT(CompPlayerControlled, player_controlled)
  ECS_DECLARE_COMPONENT(CompWall, wall)
  ECS_DECLARE_COMPONENT(CompAnimation, animation)
  ECS_DECLARE_COMPONENT(CompSprite, sprite)
  ECS_DECLARE_COMPONENT(CompTilemap, tilemap)
  ECS_DECLARE_COMPONENT(CompAIEnemyBasic, ai_enemy_basic)
  ECS_DECLARE_COMPONENT(CompBullet, bullet)
  ECS_DECLARE_COMPONENT(CompPlayerKillable, player_killable)
  ECS_DECLARE_COMPONENT(CompHudEntity, hud_entity)

private:
  std::vector<UpdateSystem *> update_systems;
  std::vector<PaintSystem *> paint_systems;
  /** A buffer of entity IDs which need to be killed after an update. */
  std::vector<EntityId> death_queue;
  int current_entity_id;

  /** Kill all the entities in the queue. */
  void kill_entities();

public:
  ECS();
  ~ECS();
  EntityId gen_entity_id();
  /** Updates the ECS */
  void update(InputState *input_state, Camera *camera,
              StandardTextures *std_tex);
  void paint(InputState *input_state, PaintController *paint_controller,
             Camera *camera, StandardTextures *std_tex);
  /** Kill an entity. Entity will be removed after all systems have finished
   * running. */
  void queue_entity_death(EntityId id);

  /** Given a (sorted) list of components and an entity ID, find
   * the component with the given entity ID */
  template <class T> static T *find_id(T *comp_list, u32 len, EntityId target_id);
};
