#pragma once
#include "resource_defs.hpp"


class Keyframe {
public:
  f32 value;
  u32 updates;
  InterpolationType interpolation_type;
  u32 part_id;

  Keyframe(f32 value, u32 updates, InterpolationType interpolation_type, u32 part_id);
};
