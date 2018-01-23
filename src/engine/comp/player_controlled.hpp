#pragma once
#include "engine/entity_id.hpp"
#include "engine/vec.hpp"
#include <cmath>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

/** Since there'll only be 1 instance of this, this class can pretty much be as
 * bloated as we like. Don't freak out about adding stuff willy nilly
 * performance wise! */
class CompPlayerControlled {
public:
  const static u8 STATE_NORMAL = 0;
  const static u8 STATE_PRE_TELEPORT = 1;
  const static u8 STATE_TELEPORTING = 2;
  const static u8 STATE_ATTACKING = 3;

  /** Length, in radians, of the player's attack arc */
  constexpr static f32 ATTACK_ARC_LEN = 2.0f * M_PI / 3.0f;
  /** The distance from the player the arc starts (thickness) */
  constexpr static f32 ATTACK_ARC_MIN_DIS = 24.0;
  /** The distance from the player the arc starts (thickness) */
  constexpr static f32 ATTACK_ARC_MAX_DIS = 30.0;

  CompPlayerControlled(EntityId entity_id, f32 force_to_apply);
  CompPlayerControlled();

  EntityId entity_id;

  /** How many more hits can we take without dying? */
  u32 life_left = 3;

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
