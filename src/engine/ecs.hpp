#pragma once

#include <cstdint>
#include <vector>
#include "comp/game_entity.hpp"
#include "system/system.hpp"

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
#define ECS_DECLARE_COMPONENT(TYPE, NAME) \
  private:\
    std::vector<TYPE> comp_NAME;\
  public:\
    void add_comp_NAME(TYPE comp);

/** Macro for generating implementations of functions to add components. When
 * declaring a component of type `CompPlayerControlled`, with the name
 * `player_controlled`, use this macro in the implementation (.cpp) file as so:
 *
 * ```
 * ECS_IMPL_COMPONENT(CompPlayerControlled, player_controlled)
 * ```
 */
#define ECS_IMPL_COMPONENT(TYPE, NAME) \
  void ECS::add_comp_NAME(TYPE comp) {\
    this->comp_NAME.push_back(comp);\
  }

/***********************/
/** Class declaration **/
/***********************/

typedef u32 EntityId;

/** Entity component system, containing lists of all the components. */
class ECS {
  /* The system class needs to access the components */
  friend class System;
  /* Auto generated component lists.. */
  ECS_DECLARE_COMPONENT(CompGameEntity, game_entity)
  private:
    std::vector<System*> systems;
  public:
    EntityId gen_entity_id();
    /** Updates the ECS */
    void update();
};
