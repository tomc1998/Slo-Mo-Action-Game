#pragma once
#include "engine/entity_id.hpp"
#include "engine/vec.hpp"

class CompPlayerControlled {
private:
  u8 state;

public:
  const static u8 STATE_NORMAL = 0;
  const static u8 STATE_PRE_TELEPORT = 1;
  const static u8 STATE_TELEPORTING = 2;
  const static u8 STATE_ATTACKING = 3;

  CompPlayerControlled(EntityId entity_id, f32 force_to_apply);

  EntityId entity_id;

  Vec2 teleport_pos;

  /** Incremented every update. Reset to 0 when state changes. */
  u32 state_change_timer;

  /** The force to apply when walking */
  f32 force_to_apply;

  /** 
   * Set the state to a given value. See the constants prefixed with STATE_
   * belonging to this class for possible values - for example,
   * CompPlayerControlled::STATE_NORMAL.
   */
  void set_state(u8 state);
  /** Get the current state. */
  u8 get_state();
};
