#pragma once
#include "comp/game_entity.hpp"
#include "comp/player_controlled.hpp"
#include "comp/wall.hpp"
#include "comp/animations.hpp"
#include <chrono>
#include <cstdint>
#include <vector>

// Forward declaration or else circular include happens
class PaintSystem;
class UpdateSystem;
class SystemPlayerControlled;
class SystemPhysics;
class SystemDebugPaint;
class SystemWallCollision;
class InputState;
class PaintController;

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
  friend class SystemDebugPaint;
  /* Auto generated component lists.. */
  ECS_DECLARE_COMPONENT(CompGameEntity, game_entity)
  ECS_DECLARE_COMPONENT(CompPlayerControlled, player_controlled)
  ECS_DECLARE_COMPONENT(CompWall, wall)
  ECS_DECLARE_COMPONENT(CompAnimations, animations)
private:
  std::vector<UpdateSystem *> update_systems;
  std::vector<PaintSystem *> paint_systems;
  int current_entity_id;

public:
  ECS();
  ~ECS();
  EntityId gen_entity_id();
  /** Updates the ECS */
  void update(InputState *input_state);
  void paint(InputState *input_state, PaintController* paint_controller);
};
