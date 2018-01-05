#pragma once
#include "engine/vec.hpp"
#include <vector>

class InputState {
public:
  f32 move_up;
  f32 move_up_prev;
  i32 move_up_keycode;

  f32 move_right;
  f32 move_right_prev;
  i32 move_right_keycode;

  f32 move_down;
  f32 move_down_prev;
  i32 move_down_keycode;

  f32 move_left;
  f32 move_left_prev;
  i32 move_left_keycode;

  bool attack_down;
  bool attack_down_prev;
  i32 attack_down_keycode;

  bool slomo_down;
  bool slomo_down_prev;
  i32 slomo_down_keycode;

  /** Vector of mouse positions throughout the drag */
  bool lmb_down;
  bool lmb_down_prev;
  std::vector<Vec2> mouse_drag;

  Vec2 mouse_pos;
};
