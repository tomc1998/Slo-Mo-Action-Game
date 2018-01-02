#include "anim_frame.hpp"
#include "animation.hpp"
#include "keyframe.hpp"
#include <cassert>
#include <functional>
#include <iostream>

f32 Animation::lerp(f32 start_value, f32 end_value, i32 start_updates,
                    i32 end_updates, i32 curr_updates) {
  return start_value + (f32)(curr_updates - start_updates) /
                           (f32)(end_updates - start_updates) *
                           (end_value - start_value);
}

u32 Animation::get_part_count() { return this->part_id_map.size(); }

void Animation::get_anim_frames(u32 updates, AnimFrame *frames) {

  if (this->posx_keys.size() == 0 && this->posy_keys.size() == 0 &&
      this->scale_keys.size() == 0 && this->rot_keys.size() == 0) {
    u32 index = 0;
    for (auto element : this->part_id_map) {
      frames[index] = AnimFrame(element.second);
      index++;
    }
    return;
  }

  u32 index = 0;
  for (auto element : this->part_id_map) {
    u32 p_id = element.first;
    TexHandle tex = element.second;

    AnimFrame frame;
    frame.tex = tex;

    std::reference_wrapper<f32> frame_val_refs[] = {frame.posx, frame.posy,
                                                    frame.scale, frame.rot};
    std::reference_wrapper<std::vector<Keyframe>> keys_refs[] = {
        posx_keys, posy_keys, scale_keys, rot_keys};

    for (u32 ii = 0; ii < sizeof(keys_refs) / sizeof(keys_refs[0]); ii++) {
      std::vector<Keyframe> &keys = keys_refs[ii];
      for (u32 jj = 0; jj < keys.size(); jj++) {
        if (keys[jj].part_id == p_id && keys[jj].updates <= updates &&
            keys[jj + 1].updates > updates) {
          Keyframe s = keys[jj];
          Keyframe e = keys[jj + 1];

          if (s.interpolation_type == LINEAR) {
            f32 &frame_val_ref = frame_val_refs[ii];
            frame_val_ref =
                lerp(s.value, e.value, s.updates, e.updates, updates);
          }
        }
      }
    }
    frames[index] = frame;
    index++;
  }
}

Animation::Animation() {
  this->part_id_map.clear();
  this->posx_keys.clear();
  this->posy_keys.clear();
  this->scale_keys.clear();
  this->rot_keys.clear();
}

Animation::Animation(std::vector<TexHandle> texs) {
  u32 index = 0;
  for (const auto &tex : texs) {
    this->part_id_map[index] = tex;
    if (index == 0) {
      this->posx_keys.push_back(Keyframe(0.0, 0, LINEAR, index));
      this->posx_keys.push_back(Keyframe(15.0, 500, LINEAR, index));
      this->posx_keys.push_back(Keyframe(0.0, 1000, LINEAR, index));

      this->posy_keys.push_back(Keyframe(0.0, 0, LINEAR, index));
      this->posy_keys.push_back(Keyframe(10.0, 333, LINEAR, index));
      this->posy_keys.push_back(Keyframe(-10.0, 666, LINEAR, index));
      this->posy_keys.push_back(Keyframe(0.0, 1000, LINEAR, index));

      this->scale_keys.push_back(Keyframe(1.0, 0, LINEAR, index));
      this->scale_keys.push_back(Keyframe(2.0, 100, LINEAR, index));
      this->scale_keys.push_back(Keyframe(1.0, 200, LINEAR, index));
      this->scale_keys.push_back(Keyframe(1.0, 800, LINEAR, index));
      this->scale_keys.push_back(Keyframe(2.0, 900, LINEAR, index));
      this->scale_keys.push_back(Keyframe(1.0, 1000, LINEAR, index));

      this->rot_keys.push_back(Keyframe(0.0, 0, LINEAR, index));
      this->rot_keys.push_back(Keyframe(-6.28, 1000, LINEAR, index));
    } else {
      this->posx_keys.push_back(Keyframe(0.0, 0, LINEAR, index));
      this->posx_keys.push_back(Keyframe(-15.0, 500, LINEAR, index));
      this->posx_keys.push_back(Keyframe(0.0, 1000, LINEAR, index));

      this->posy_keys.push_back(Keyframe(0.0, 0, LINEAR, index));
      this->posy_keys.push_back(Keyframe(-10.0, 333, LINEAR, index));
      this->posy_keys.push_back(Keyframe(10.0, 666, LINEAR, index));
      this->posy_keys.push_back(Keyframe(0.0, 1000, LINEAR, index));

      this->scale_keys.push_back(Keyframe(1.0, 0, LINEAR, index));
      this->scale_keys.push_back(Keyframe(2.0, 100, LINEAR, index));
      this->scale_keys.push_back(Keyframe(1.0, 200, LINEAR, index));
      this->scale_keys.push_back(Keyframe(1.0, 800, LINEAR, index));
      this->scale_keys.push_back(Keyframe(2.0, 900, LINEAR, index));
      this->scale_keys.push_back(Keyframe(1.0, 1000, LINEAR, index));

      this->rot_keys.push_back(Keyframe(0.0, 0, LINEAR, index));
      this->rot_keys.push_back(Keyframe(6.28, 1000, LINEAR, index));
    }
    index++;
  }
}
