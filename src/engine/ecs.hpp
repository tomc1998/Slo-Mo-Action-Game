#pragma once
#include "comp/ai_enemy_basic.hpp"
#include "comp/animation.hpp"
#include "comp/bullet.hpp"
#include "comp/circle_collider.hpp"
#include "comp/game_entity.hpp"
#include "comp/hud_entity.hpp"
#include "comp/player_controlled.hpp"
#include "comp/player_killable.hpp"
#include "comp/sprite.hpp"
#include "comp/tilemap.hpp"
#include "comp/wall.hpp"
#include <chrono>
#include <cstdint>
#include <vector>

class PaintSystem;
class UpdateSystem;
class InputState;
class PaintController;
class StandardTextures;
class Camera;
class Globals;

/************/
/** MACROS **/
/************/


/** Runs the macro X(T, N) on all the components, where the T parameter is the
 * type and N is the name of the component.
 * The idea of this is to define X(T,N) before calling this macro and then
 * un-defing the X() macro. This allows some code to be run on all the
 * components. */
#define RUN_X_MACRO_ON_ALL_COMPS                                               \
  X(CompGameEntity, game_entity)                                               \
  X(CompPlayerControlled, player_controlled)                                   \
  X(CompWall, wall)                                                            \
  X(CompAnimation, animation)                                                  \
  X(CompSprite, sprite)                                                        \
  X(CompTilemap, tilemap)                                                      \
  X(CompAIEnemyBasic, ai_enemy_basic)                                          \
  X(CompBullet, bullet)                                                        \
  X(CompPlayerKillable, player_killable)                                       \
  X(CompHudEntity, hud_entity)                                                 \
  X(CompCircleCollider, circle_collider)

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
  friend class SystemShadowRenderer;
  friend class Editor;

/** Generate component list declarations */
#define X(TYPE, NAME)                                      \
private:                                                                       \
  std::vector<TYPE> comp_##NAME;                                               \
                                                                               \
public:                                                                        \
  void add_comp_##NAME(TYPE comp);                                             \
  TYPE *find_comp_##NAME##_with_id(EntityId entity_id);
RUN_X_MACRO_ON_ALL_COMPS
#undef X

private:
  std::vector<UpdateSystem *> update_systems;
  std::vector<PaintSystem *> paint_systems;
  /** A buffer of entity IDs which need to be killed after an update. */
  std::vector<EntityId> death_queue;
  i32 current_entity_id;

  /** Kill all the entities in the queue. */
  void kill_entities();

public:
  ECS();
  ~ECS();
  EntityId gen_entity_id();
  /** Updates the ECS */
  void update(Globals& globals);
  void paint(Globals& globals);
  /** Kill an entity. Entity will be removed after all systems have finished
   * running. */
  void queue_entity_death(EntityId id);

  /** Given a (sorted) list of components and an entity ID, find
   * the component with the given entity ID */
  template <class T>
  static T *find_id(T *comp_list, u32 len, EntityId target_id);
};
