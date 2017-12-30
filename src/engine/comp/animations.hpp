#pragma once
#include "engine/entity_id.hpp"
#include "engine/vec.hpp"
#include <vector>

class Animation;
typedef i32 ResHandle;
/**
 * A component which stores a vector of pointers to animation resources */

class CompAnimations {
public:
  CompAnimations(EntityId entity_id, std::vector<Animation *> animations,
                 ResHandle th);

  EntityId entity_id;
  std::vector<Animation *> animations;

  /** Stores which animation index should be played next
   * -1 indicates no animation should be played*/

  i32 animation_to_play;
  i32 updates;

  /** to be used if animation_to_play is -1 */
  ResHandle th;
};
