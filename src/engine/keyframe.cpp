#include "keyframe.hpp"
#include "animation.hpp"

Keyframe::Keyframe(f32 value, u32 updates, InterpolationType interpolation_type, u32 part_id) {
  this->value = value;
  this->updates = updates;
  this->interpolation_type = interpolation_type;
  this->part_id = part_id;
}
