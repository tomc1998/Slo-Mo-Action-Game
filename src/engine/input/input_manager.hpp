#pragma once
#include "input_state.hpp"

// Forward declarations
class GLFWwindow;

/** Input manager class that updates input and stores it in an InputState
 * variable*/
class InputManager {
private:
  InputState current_input_state;

public:
  InputManager(GLFWwindow *window);
  InputState *get_current_input_state();
  /** Key callback function to deal with events */
  static void key_callback(GLFWwindow *window, int key, int scancode,
                           int action, int mods);
  /** Mouse callback function to handle mouse input */
  static void mouse_callback(GLFWwindow *window, int button, int action,
                             int mods);
  /** Polls events and changes the current_input_state */
  void update_input();
};
