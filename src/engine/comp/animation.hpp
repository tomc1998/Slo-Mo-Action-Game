#pragma once
#include "engine/entity_id.hpp"
#include "engine/vec.hpp"
#include "engine/resource_defs.hpp"
#include <vector>

class Animation;
/**
 * A component which stores a vector of pointers to animation resources */

class CompAnimation {
public:
  CompAnimation(EntityId entity_id, AnimHandle ah, i32 length);

  EntityId entity_id;
  AnimHandle ah;
  i32 length;

  /** Stores the current timestamp of this animation */
  i32 updates;

};
