#include "anim_frame.hpp"
#include "animation.hpp"
#include "keyframe.hpp"
#include <cassert>
#include <iostream>

f32 Animation::lerp(f32 start_value, f32 end_value, i32 start_updates,
                    i32 end_updates, i32 curr_updates) {
  return start_value + (f32)(curr_updates - start_updates) /
                           (f32)(end_updates - start_updates) *
                           (end_value - start_value);
}

u32 Animation::get_part_count() { return this->part_id_map.size(); }

void Animation::get_anim_frames(u32 updates, AnimFrame frames[]) {

  if (this->posx_keys.size() == 0 && this->posy_keys.size() == 0 &&
      this->scale_keys.size() == 0 && this->rot_keys.size() == 0) {
    u32 it = 0;
    for (auto element : this->part_id_map) {
      frames[it] = AnimFrame(element.second);
      it++;
    }
    return;
  }

  u32 it = 0;
  for (auto element : this->part_id_map) {
    u32 p_id = element.first;
    TexHandle th = element.second;

    AnimFrame frame;
    frame.th = th;

    for (u32 ii = 0; ii < this->posx_keys.size(); ii++) {
      if (this->posx_keys[ii].part_id == p_id &&
          this->posx_keys[ii].updates <= updates &&
          this->posx_keys[ii + 1].updates > updates) {
        Keyframe s = this->posx_keys[ii];
        Keyframe e = this->posx_keys[ii + 1];

        if (s.interpolation_type == LINEAR) {
          frame.posx = lerp(s.value, e.value, s.updates, e.updates, updates);
        }
        break;
      } else {
        frame.posx = 0.0;
      }
    }

    for (u32 ii = 0; ii < this->posy_keys.size(); ii++) {
      if (this->posy_keys[ii].part_id == p_id &&
          this->posy_keys[ii].updates <= updates &&
          this->posy_keys[ii + 1].updates > updates) {
        Keyframe s = this->posy_keys[ii];
        Keyframe e = this->posy_keys[ii + 1];

        if (s.interpolation_type == LINEAR) {
          frame.posy = lerp(s.value, e.value, s.updates, e.updates, updates);
        }
        break;
      } else {
        frame.posy = 0.0;
      }
    }

    for (u32 ii = 0; ii < this->scale_keys.size(); ii++) {
      if (this->scale_keys[ii].part_id == p_id &&
          this->scale_keys[ii].updates <= updates &&
          this->scale_keys[ii + 1].updates > updates) {
        Keyframe s = this->scale_keys[ii];
        Keyframe e = this->scale_keys[ii + 1];

        if (s.interpolation_type == LINEAR) {
          frame.scale = lerp(s.value, e.value, s.updates, e.updates, updates);
        }
        break;
      } else {
        frame.scale = 1.0;
      }
    }

    for (u32 ii = 0; ii < this->rot_keys.size(); ii++) {
      if (this->rot_keys[ii].part_id == p_id &&
          this->rot_keys[ii].updates <= updates &&
          this->rot_keys[ii + 1].updates > updates) {
        Keyframe s = this->rot_keys[ii];
        Keyframe e = this->rot_keys[ii + 1];

        if (s.interpolation_type == LINEAR) {
          frame.rot = lerp(s.value, e.value, s.updates, e.updates, updates);
        }
        break;
      } else {
        frame.rot = 0.0;
      }
    }

    frames[it] = frame;
    it++;
  }
}

Animation::Animation() {
  this->part_id_map.clear();
  this->posx_keys.clear();
  this->posy_keys.clear();
  this->scale_keys.clear();
  this->rot_keys.clear();
}

Animation::Animation(std::vector<TexHandle> ths) {
  u32 it = 0;
  for (const auto &th : ths) {
    this->part_id_map[it] = th;
    if (it == 0) {
      this->scale_keys.push_back(Keyframe(0.0, 0, LINEAR, it));
      this->scale_keys.push_back(Keyframe(5.0, 100, LINEAR, it));
      this->scale_keys.push_back(Keyframe(0.0, 200, LINEAR, it));
    } else {
      this->scale_keys.push_back(Keyframe(0.0, 0, LINEAR, it));
      this->scale_keys.push_back(Keyframe(2.0, 50, LINEAR, it));
      this->scale_keys.push_back(Keyframe(0.0, 100, LINEAR, it));
      this->scale_keys.push_back(Keyframe(2.0, 150, LINEAR, it));
      this->scale_keys.push_back(Keyframe(0.0, 200, LINEAR, it));
    }
    it++;
  }
}
