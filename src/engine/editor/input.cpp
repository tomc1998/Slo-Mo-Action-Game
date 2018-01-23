#include "input.hpp"
#include <cstdlib>
#include <iostream>

EditorInput* EditorInput::instance = new EditorInput();

EditorInput::EditorInput() { }

void EditorInput::key_input(int key, int scancode, int action, int mods) {
  std::cout << "Editor key input" << std::endl;
}

void EditorInput::cursor_pos_input(double xpos, double ypos) {
  std::cout << "Editor cursor pos input" << std::endl;
}

void EditorInput::mouse_input(int button, int action, int mods) {
  std::cout << "Editor mouse input" << std::endl;
}

