#pragma once
#include "engine/entity_id.hpp"
#include "engine/vec.hpp"
#include <vector>

/** An AI component for basic enemy behaviour. */
class CompAIEnemyBasic {

public:
  EntityId entity_id;

private:
  u8 state = STATE_NORMAL;

public:
  CompAIEnemyBasic();
  CompAIEnemyBasic(EntityId entity_id);

  const static u16 RELOAD_TIME = 300;
  const static u8 STATE_NORMAL = 0;
  /** This state will be set when the player is in view, but the AI hasn't
   * reacted yet */
  const static u8 STATE_WAITING_ON_REACTION = 1;
  const static u8 SPOTTED_PLAYER = 2;

  /** Incremented every update. Reset to 0 when state changes. */
  u32 state_change_timer = 0;

  /** Upon seeing the player, how long (in game ticks) does it take to respond?
   */
  u16 reaction_delay = 150;

  /** When this reaches RELOAD_TIME, this entity will shoot */
  u16 reload_timer = 0;

  /** Vector of target waypoints to visit */
  std::vector<Vec2> target_waypoints;

  /** Force to apply when moving */
  f32 force_to_apply = 400.0;

  /**
   * Set the state to a given value.
   */
  void set_state(u8 state);
  /** Get the current state. */

  u8 get_state() const;
};
