#pragma once
#include "engine/entity_id.hpp"

/** Attach this component to anything which can be hit and killed by the player.
 * Must have a game_entity component. */
class CompPlayerKillable {
public:
  CompPlayerKillable(EntityId entity_id, u32 life_left);
  CompPlayerKillable(EntityId entity_id);
  CompPlayerKillable();

  EntityId entity_id;

  /** How many times this entity can be hit before being removed */
  u32 life_left = 3;

  /** How many ticks of invincibility do we have left? (decremented to 0 every
   * update in check_death system) */
  u32 inv_frames = 0;
};
