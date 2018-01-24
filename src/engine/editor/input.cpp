#include "input.hpp"
#include <cstdlib>
#include <iostream>

#include <glad/glad.h>

#include <GLFW/glfw3.h>

EditorInput *EditorInput::instance = new EditorInput();

EditorInput::EditorInput() { codepoint_buf.reserve(16); }

void EditorInput::key_input(int key, int scancode, int action, int mods) {
  switch (key) {
  case GLFW_KEY_A:
    if (mods & GLFW_MOD_SHIFT) {
      add_entity_handle_glfw_action(action);
    }
    break;
  case GLFW_KEY_F1:
    toggle_library_handle_glfw_action(action);
    break;
  }
}

void EditorInput::cursor_pos_input(double xpos, double ypos) {}

void EditorInput::mouse_input(int button, int action, int mods) {
  switch (button) {
  case GLFW_MOUSE_BUTTON_LEFT:
    lmb_handle_glfw_action(action);
    break;
  case GLFW_MOUSE_BUTTON_RIGHT:
    rmb_handle_glfw_action(action);
    break;
  }
}

void EditorInput::char_input(unsigned int codepoint) {
  codepoint_buf.push_back(codepoint);
}

#define X(INPUT)                                                               \
  void EditorInput::INPUT##_handle_glfw_action(int action) {                   \
    if (action == GLFW_PRESS) {                                                \
      INPUT##_down = true;                                                     \
    } else if (action == GLFW_RELEASE) {                                       \
      INPUT##_down = false;                                                    \
    }                                                                          \
  }                                                                            \
  bool EditorInput::INPUT##_just_pressed() {                                   \
    return INPUT##_down && !INPUT##_down_prev;                                 \
  }                                                                            \
  bool EditorInput::INPUT##_just_released() {                                  \
    return !INPUT##_down && INPUT##_down_prev;                                 \
  }
RUN_X_MACRO_ON_ALL_EDITOR_INPUTS
#undef X

void EditorInput::update_input() {
#define X(INPUT) INPUT##_down_prev = INPUT##_down;
  RUN_X_MACRO_ON_ALL_EDITOR_INPUTS
#undef X
  codepoint_buf.clear();
}
