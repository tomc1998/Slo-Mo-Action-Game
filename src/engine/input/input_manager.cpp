#include "engine/canvas_size.hpp"
#include "engine/editor/input.hpp"
#include "engine/vec.hpp"
#include "input_manager.hpp"
#include "input_state.hpp"
#include <iostream>

#include <glad/glad.h>

#include <GLFW/glfw3.h>

InputManager::InputManager(GLFWwindow *window) {
  current_input_state.move_up_keycode = GLFW_KEY_W;
  current_input_state.move_right_keycode = GLFW_KEY_D;
  current_input_state.move_down_keycode = GLFW_KEY_S;
  current_input_state.move_left_keycode = GLFW_KEY_A;
  current_input_state.slomo_down_keycode = GLFW_KEY_SPACE;
  current_input_state.editor_toggle_keycode = GLFW_KEY_TAB;

  current_input_state.move_up = 0.0f;
  current_input_state.move_right = 0.0f;
  current_input_state.move_down = 0.0f;
  current_input_state.move_left = 0.0f;
  current_input_state.slomo_down = false;
  current_input_state.lmb_down = false;
  current_input_state.rmb_down = false;

  glfwSetKeyCallback(window, InputManager::key_callback);
  glfwSetMouseButtonCallback(window, InputManager::mouse_callback);
  glfwSetCursorPosCallback(window, InputManager::cursor_position_callback);
  glfwSetWindowUserPointer(window, &this->current_input_state);
}

InputState *InputManager::get_current_input_state() {
  return &this->current_input_state;
}

void InputManager::key_callback(GLFWwindow *window, int key, int scancode,
                                int action, int mods) {
  InputState *input_state = (InputState *)glfwGetWindowUserPointer(window);

  // Feed input to editor
  EditorInput::instance->key_input(key, scancode, action, mods);

  // Key presses
  if (action == GLFW_PRESS) {
    if (key == input_state->move_up_keycode) {
      input_state->move_up = 1.0f;
    }

    if (key == input_state->move_right_keycode) {
      input_state->move_right = 1.0f;
    }

    if (key == input_state->move_down_keycode) {
      input_state->move_down = 1.0f;
    }

    if (key == input_state->move_left_keycode) {
      input_state->move_left = 1.0f;
    }

    if (key == input_state->slomo_down_keycode) {
      input_state->slomo_down = true;
    }

    if (key == input_state->editor_toggle_keycode) {
      input_state->editor_toggle_down = true;
    }
  }

  // Key releases
  if (action == GLFW_RELEASE) {
    if (key == input_state->move_up_keycode) {
      input_state->move_up = 0.0f;
    }

    if (key == input_state->move_right_keycode) {
      input_state->move_right = 0.0f;
    }

    if (key == input_state->move_down_keycode) {
      input_state->move_down = 0.0f;
    }

    if (key == input_state->move_left_keycode) {
      input_state->move_left = 0.0f;
    }

    if (key == input_state->slomo_down_keycode) {
      input_state->slomo_down = false;
    }

    if (key == input_state->editor_toggle_keycode) {
      input_state->editor_toggle_down = false;
    }
  }
}

void InputManager::mouse_callback(GLFWwindow *window, int button, int action,
                                  int mods) {
  InputState *input_state = (InputState *)glfwGetWindowUserPointer(window);
  double xpos, ypos;

  // Feed input to editor
  EditorInput::instance->mouse_input(button, action, mods);

  if (action == GLFW_PRESS) {
    if (button == GLFW_MOUSE_BUTTON_LEFT) {
      input_state->lmb_down = true;
      glfwGetCursorPos(window, &xpos, &ypos);
      input_state->lmb_drag.push_back(Vec2((f32)xpos, (f32)ypos));
    } else if (button == GLFW_MOUSE_BUTTON_RIGHT) {
      input_state->rmb_down = true;
      glfwGetCursorPos(window, &xpos, &ypos);
      input_state->rmb_drag.push_back(Vec2((f32)xpos, (f32)ypos));
    }
  } else if (action == GLFW_RELEASE) {
    if (button == GLFW_MOUSE_BUTTON_LEFT) {
      input_state->lmb_down = false;
    } else if (button == GLFW_MOUSE_BUTTON_RIGHT) {
      input_state->rmb_down = false;
    }
  }

  // If mouse is down, add the coordinates to the X_drag vector
  // If mouse is released and the X_drag vector is not already empty,
  // empty it
  if (!input_state->lmb_down && input_state->lmb_drag.size() != 0) {
    input_state->lmb_drag.clear();
  }
  if (!input_state->rmb_down && input_state->rmb_drag.size() != 0) {
    input_state->rmb_drag.clear();
  }
}

void InputManager::cursor_position_callback(GLFWwindow *window, double xpos,
                                            double ypos) {
  InputState *input_state = (InputState *)glfwGetWindowUserPointer(window);

  // We need to transform this onto the viewport before anything else touches
  // it - i.e. so that the point is inside our letterboxing
  i32 viewport[4];
  glGetIntegerv(GL_VIEWPORT, viewport);
  Vec2 viewport_pos((f32)viewport[0], (f32)viewport[1]);
  Vec2 mouse_pos((f32)xpos, (f32)ypos);
  Vec2 transformed = mouse_pos - viewport_pos;
  transformed.x *= ((f32)CANVAS_W / (f32)viewport[2]);
  transformed.y *= ((f32)CANVAS_H / (f32)viewport[3]);

  input_state->mouse_pos = transformed;

  // Feed input to editor
  EditorInput::instance->cursor_pos_input(transformed.x, transformed.y);
}

void InputManager::update_input() {
  // Remember the previous values of each input
  current_input_state.move_up_prev = current_input_state.move_up;
  current_input_state.move_right_prev = current_input_state.move_right;
  current_input_state.move_down_prev = current_input_state.move_down;
  current_input_state.move_left_prev = current_input_state.move_left;
  current_input_state.slomo_down_prev = current_input_state.slomo_down;
  current_input_state.lmb_down_prev = current_input_state.lmb_down;
  current_input_state.rmb_down_prev = current_input_state.rmb_down;
  current_input_state.editor_toggle_down_prev =
      current_input_state.editor_toggle_down;
  glfwPollEvents();
  if (current_input_state.lmb_down) {
    current_input_state.lmb_drag.push_back(current_input_state.mouse_pos);
  }
  if (current_input_state.rmb_down) {
    current_input_state.rmb_drag.push_back(current_input_state.mouse_pos);
  }
}
