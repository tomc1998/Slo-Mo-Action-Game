#pragma once
#include "engine/vec.hpp"
#include <vector>

/** TODO: Find way of binding constrols to multiple controls (just referencing
 * keycodes doesn't a allow binding to mouse buttons) */
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

  bool editor_toggle_down = false;
  bool editor_toggle_down_prev = false;
  i32 editor_toggle_keycode;

  bool slomo_down = false;
  bool slomo_down_prev = false;
  i32 slomo_down_keycode;

  /** LMB = attack control */
  bool lmb_down = false;
  bool lmb_down_prev = false;
  /** Vector of mouse positions throughout the drag */
  std::vector<Vec2> lmb_drag;

  /** RMB = teleport control */
  bool rmb_down = false;
  bool rmb_down_prev = false;
  /** Vector of mouse positions throughout the drag */
  std::vector<Vec2> rmb_drag;

  Vec2 mouse_pos;
};
