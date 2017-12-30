#pragma once
#include "engine/entity_id.hpp"
#include "engine/resource.hpp"
#include "engine/vec.hpp"

/**
 * A component which stores a vector of pointers to an animation resource */

class CompAnimation {
public:
  CompAnimation(EntityId entity_id, std::vector<Animation *> animations);

  EntityId entity_id;
  std::vector<Animation *> animations;

  /** Stores which animation index should be played next 
   * -1 indicates no animation should be played*/

  i32 animation_to_play;
};
