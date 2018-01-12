#pragma once

#include "engine/entity_id.hpp"
#include "engine/resource_defs.hpp"

/** A component for rendering a sprite at the position of a gameentity. */
class CompSprite {
  public:
    EntityId entity_id;
    TexHandle tex;
    CompSprite(EntityId entity_id, TexHandle tex);
};

