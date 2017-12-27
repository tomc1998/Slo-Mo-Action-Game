#pragma once

typedef u32 EntityId;

class CompPlayerControlled {
  public:
    CompPlayerControlled(f32 force_to_apply, EntityId entity_id);
    f32 force_to_apply;
    EntityId entity_id;
};
