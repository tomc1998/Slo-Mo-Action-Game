#pragma once
#include "engine/entity_id.hpp"
#include "engine/vec.hpp"

class CompPlayerControlled {
public:
  const static u8 STATE_NORMAL = 0;
  const static u8 STATE_PRE_TELEPORT = 1;
  const static u8 STATE_TELEPORTING = 2;

  CompPlayerControlled(EntityId entity_id, f32 force_to_apply);

  Vec2 teleport_pos;
  u32 state_change_timer;
  u8 state;
  EntityId entity_id;
  f32 force_to_apply;
};
