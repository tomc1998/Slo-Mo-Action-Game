#pragma once
#include "engine/entity_id.hpp"

/** Attach this component to anything which can be hit and killed by the player.
 * Must have a game_entity component. */
class CompPlayerKillable {
public:
  CompPlayerKillable(EntityId entity_id, float hit_rad, u32 life_left);
  CompPlayerKillable(EntityId entity_id);

  EntityId entity_id;
  /** The radius of the circular hitbox */
  float hit_rad = 8.0;
  /** How many times this entity can be hit before being removed */
  u32 life_left = 3;
};
