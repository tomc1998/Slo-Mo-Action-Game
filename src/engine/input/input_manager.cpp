#include <GLFW/glfw3.h>
#include <iostream>
#include "engine/vec.hpp"  
#include "input_manager.hpp"
#include "input_state.hpp"

InputManager::InputManager(GLFWwindow* window) {
  glfwSetKeyCallback(window, this->key_callback);
  glfwSetMouseButtonCallback(window, this->mouse_callback);

  glfwSetWindowUserPointer(window, &this->current_input_state);
}

InputState* InputManager::get_current_input_state() {
  return &this->current_input_state;
}

void InputManager::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
  InputState* input_state = (InputState*)glfwGetWindowUserPointer(window);

  // Remember the previous values of each input
  input_state->move_up_prev = input_state->move_up;
  input_state->move_right_prev = input_state->move_right;
  input_state->move_down_prev = input_state->move_down;
  input_state->move_left_prev = input_state->move_left;
  input_state->attack_down_prev = input_state->attack_down;
  input_state->slomo_down_prev = input_state->move_up;

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

    if (key == input_state->attack_down_keycode) {
      input_state->attack_down = true;
    }

    if (key == input_state->slomo_down_keycode) {
      input_state->slomo_down = true;
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

    if (key == input_state->attack_down_keycode) {
      input_state->attack_down = false;
    }

    if (key == input_state->slomo_down_keycode) {
      input_state->slomo_down = false;
    }
  }
   
}

void InputManager::mouse_callback(GLFWwindow* window, int button, int action, int mods) {
  InputState* input_state = (InputState*)glfwGetWindowUserPointer(window);
  double xpos, ypos;

  if (action == GLFW_PRESS) {
    if (button == GLFW_MOUSE_BUTTON_LEFT) {
      input_state->lmb_down = true;
    }
  }
  if (action == GLFW_RELEASE) {
    if (button == GLFW_MOUSE_BUTTON_LEFT) {
      input_state->lmb_down = false;
    }
  }

  // If lmb is down, add the coordinates to the mouse_drag vector
  if (input_state->lmb_down) {
    glfwGetCursorPos(window, &xpos, &ypos);
    input_state->mouse_drag.push_back(Vec2((f32)xpos, (f32)ypos));
  }
  //If lmb is released and the mouse_drag vector is not already empty, empty it
  else if (not(input_state->lmb_down) && input_state->mouse_drag.size() != 0) {
    input_state->mouse_drag.clear();
  }
  
}

void InputManager::update_input() {
  glfwPollEvents();
}

