#pragma once
#include "engine/vec.hpp"

/**
 * A component for game entities (i.e. things which have an in-world position,
 * interact w/ physics, etc)
 */
class CompGameEntity {
  Vec2<f32> pos;
};
