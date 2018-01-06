#pragma once
#include "engine/entity_id.hpp"
#include "engine/vec.hpp"

/** Since there'll only be 1 instance of this, this class can pretty much be as
 * bloated as we like. Don't freak out about adding stuff willy nilly
 * performance wise! */
class CompPlayerControlled {
public:
  const static u8 STATE_NORMAL = 0;
  const static u8 STATE_PRE_TELEPORT = 1;
  const static u8 STATE_TELEPORTING = 2;
  const static u8 STATE_ATTACKING = 3;

  CompPlayerControlled(EntityId entity_id, f32 force_to_apply);

  EntityId entity_id;

  /** When teleporting, this is the destination for the teleport. This value
   * only means something if state == STATE_TELEPORTING. */
  Vec2 teleport_pos;

  /** The angle (in radians) that the player is attacking. This value only
   * means something if state == STATE_ATTACKING. */
  f32 attack_angle;

  /** Incremented every update. Reset to 0 when state changes. */
  u32 state_change_timer;

  /** The force to apply when walking. Will generally remain constant. */
  f32 force_to_apply;

  /**
   * Set the state to a given value. See the constants prefixed with STATE_
   * belonging to this class for possible values - for example,
   * CompPlayerControlled::STATE_NORMAL.
   */
  void set_state(u8 state);
  /** Get the current state. */
  u8 get_state();

private:
  u8 state;
};
