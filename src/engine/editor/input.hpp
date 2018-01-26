#pragma once

#include "engine/vec.hpp"

#include <vector>

#define RUN_X_MACRO_ON_ALL_EDITOR_INPUTS                                       \
  X(add_entity)     /* shift + a */                                            \
  X(toggle_library) /* f1 */                                                   \
  X(lmb)                                                                       \
  X(rmb)

/**
 * A singleton class for editor input. This is separate to the normal in-game
 * input state, as we don't need keybindings for this, and we want the game
 * input state to remain relatively bloat-free.
 *
 * Keybingdings are written as doc comments directly before the pair of bools
 * indicating the key input.
 *
 * See instance member to get an instance of this editor input.
 */
class EditorInput {
private:
  EditorInput();


public:
  static EditorInput *instance;

  Vec2 mouse_pos = Vec2(0.0, 0.0);

  /** A buffer of codepoints input by the user in this frame. */
  std::vector<unsigned int> codepoint_buf;

#define X(INPUT)                                                               \
  bool INPUT##_down = false;                                                   \
  bool INPUT##_down_prev = false;                                              \
  void INPUT##_handle_glfw_action(int action);                                 \
  bool INPUT##_just_pressed();                                                 \
  bool INPUT##_just_released();
  RUN_X_MACRO_ON_ALL_EDITOR_INPUTS
#undef X

  /** This should be called from the glfw input callback function. */
  void key_input(int key, int scancode, int action, int mods);

  /** This should be called from the glfw input callback function. Should be
   * transformed onto the viewport.*/
  void cursor_pos_input(double xpos, double ypos);

  /** This should be called from the glfw input callback function. */
  void mouse_input(int button, int action, int mods);

  /** This should be called from the glfw unicode key input callback function. */
  void char_input(unsigned int codepoint);

  /** Should be called each frame, resets prev inputs */
  void update_input();
};
