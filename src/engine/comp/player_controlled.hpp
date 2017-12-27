#pragma once
#include "engine/entity_id.hpp"

class CompPlayerControlled {
public:
  CompPlayerControlled(EntityId entity_id, f32 force_to_apply);
  EntityId entity_id;
  f32 force_to_apply;
};
