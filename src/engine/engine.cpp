#include <utility>
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "engine/input/input_manager.hpp"
#include "ecs.hpp"
#include "engine.hpp"
#include "screen.hpp"

Engine::Engine() {
  glfwInit();
  this->window = glfwCreateWindow(800, 600, "Slo-Mo Action Game", NULL, NULL);
  glfwMakeContextCurrent(window);
  gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);

  this->input_manager = new InputManager(this->window);
}

void Engine::push_screen(Screen* screen) {
  this->screen_stack.push_back(std::pair<ECS*, Screen*> (new ECS(), screen));
}

void Engine::pop_screen() {
  std::pair<ECS*, Screen*> back = screen_stack.back();
  delete back.first;
  delete back.second;
  screen_stack.pop_back();
}

void Engine::engine_go() {
  this->input_manager->update_input();

  // Update the state
  //this->update();

  //TODO: Render
  //render()
}

void Engine::update() {
  ECS* current_ecs = this->screen_stack.back().first;
  current_ecs->update();
}
