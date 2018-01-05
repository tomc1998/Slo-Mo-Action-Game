#pragma once
#include "engine/entity_id.hpp"

class CompPlayerControlled {
public:
  const static u8 NORMAL = 0;
  const static u8 PRE_TELEPORT = 1;
  const static u8 TELEPORTING = 2;

  CompPlayerControlled(EntityId entity_id, f32 force_to_apply);

  u8 state;
  EntityId entity_id;
  f32 force_to_apply;
};
