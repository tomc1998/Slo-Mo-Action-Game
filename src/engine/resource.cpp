#include "anim_frame.hpp"
#include "keyframe.hpp"
#include "resource.hpp"
#include <cassert>

f32 Animation::lerp(f32 start_value, f32 end_value, i32 start_updates, i32 end_updates,
         i32 curr_updates) {
  return start_value + (f32)curr_updates / (f32)(end_updates - start_updates) *
                           (end_value - start_value);
}

AnimFrame Animation::get_anim_frame(i32 updates) {

  AnimFrame frame;

  // pos x
  i32 keyframe_ix = -1;
  for (u32 ii = 0; ii < this->posx_keys.size(); ii++) {
    if (this->posx_keys[ii].updates < updates) {
      keyframe_ix = ii;
      break;
    }
  }
  assert(keyframe_ix != -1);

  Keyframe s = this->posx_keys[keyframe_ix];
  Keyframe e = this->posx_keys[keyframe_ix + 1];
  if (this->posx_interps[keyframe_ix] == LINEAR) {
    frame.posx = lerp(s.value, e.value, s.updates, e.updates, updates);
  }

  // pos y
  keyframe_ix = -1;
  for (u32 ii = 0; ii < this->posy_keys.size(); ii++) {
    if (this->posy_keys[ii].updates < updates) {
      keyframe_ix = ii;
      break;
    }
  }
  assert(keyframe_ix != -1);

  s = this->posy_keys[keyframe_ix];
  e = this->posy_keys[keyframe_ix + 1];
  if (this->posy_interps[keyframe_ix] == LINEAR) {
    frame.posy = lerp(s.value, e.value, s.updates, e.updates, updates);
  }

  // scale
  keyframe_ix = -1;
  for (u32 ii = 0; ii < this->scale_keys.size(); ii++) {
    if (this->scale_keys[ii].updates < updates) {
      keyframe_ix = ii;
      break;
    }
  }
  assert(keyframe_ix != -1);

  s = this->scale_keys[keyframe_ix];
  e = this->scale_keys[keyframe_ix + 1];
  if (this->scale_interps[keyframe_ix] == LINEAR) {
    frame.scale = lerp(s.value, e.value, s.updates, e.updates, updates);
  }

  // rot
  keyframe_ix = -1;
  for (u32 ii = 0; ii < this->rot_keys.size(); ii++) {
    if (this->rot_keys[ii].updates < updates) {
      keyframe_ix = ii;
      break;
    }
  }
  assert(keyframe_ix != -1);

  s = this->rot_keys[keyframe_ix];
  e = this->rot_keys[keyframe_ix + 1];
  if (this->rot_interps[keyframe_ix] == LINEAR) {
    frame.rot = lerp(s.value, e.value, s.updates, e.updates, updates);
  }
  return frame;
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
Resource::~Resource() {}
Resource &Resource::operator=(const Resource &other) {
  this->data = other.data;
  this->type = other.type;
  return *this;
}
