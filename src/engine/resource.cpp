#include "keyframe.hpp"
#include "resource.hpp"
#include <cassert>

f32 Animation::linear_interpolation(f32 start_value, f32 end_value,
                                    i32 start_updates, i32 end_updates,
                                    i32 curr_updates) {
  return start_value + (f32)curr_updates / (f32)(end_updates - start_updates) *
                           (end_value - start_value);
}

f32 Animation::get_interpolated_value(i32 updates, i32 keyframe_type) {

  // There should only be a certain amount of keyframe types
  assert(keyframe_type >= 0 && keyframe_type < this->keyframes.size());

  i32 keyframe_ix = -1;
  for (i32 ii = 0; ii < this->keyframes[keyframe_type].size(); ii++) {
    if (this->keyframes[keyframe_type][ii].updates < updates) {
      keyframe_ix == ii;
      break;
    }
  }

  assert(keyframe_ix != -1);

  if (this->interpolations[keyframe_type][keyframe_ix] == LINEAR) {
    s = this->keyframes[keyframe_type][keyframe_ix];
    e = this->keyframes[keyframe_type][keyframe_ix + 1];

    return this->linear_interpolation(s.value, e.value, s.updates, e.updates,
                                      updates);
  }

  Resource::Resource(Texture t) {
    type = ResourceType::TEXTURE;
    data.texture = t;
  }

  Resource::Resource(Animation a) {
    type = ResourceType::ANIMATION;
    data.animation = a;
  }

  Resource::Resource() {}
