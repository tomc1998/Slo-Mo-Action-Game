#include <utility>
#include <iostream>
#include "engine/input/input_manager.hpp"
#include "engine/ecs.hpp"
#include "engine/engine.hpp"
#include "engine/screen.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

Engine::Engine() {
  glfwInit();
  this->window = glfwCreateWindow(800, 600, "Slo-Mo Action Game", NULL, NULL);
  glfwMakeContextCurrent(window);
  gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);

  this->renderer = new Renderer(800.0, 600.0);
  this->input_manager = new InputManager(this->window);
}

void Engine::push_screen(Screen* screen) {
  ECS* ecs = new ECS();
  screen->init(ecs);
  this->screen_stack.push_back(std::pair<ECS*, Screen*> (ecs, screen));
}

void Engine::pop_screen() {
  std::pair<ECS*, Screen*> back = screen_stack.back();
  delete back.first;
  delete back.second;
  screen_stack.pop_back();
}

void Engine::engine_go() {
  while (true) {
    this->input_manager->update_input();

    glClear(GL_COLOR_BUFFER_BIT);
    this->update();

    renderer->render();
    renderer->clear_paint_buffer();
    
    glfwSwapBuffers(this->window);
    if (glfwWindowShouldClose(this->window)){
      break;
    }
  }
}

void Engine::update() {
  ECS* current_ecs = this->screen_stack.back().first;
  auto controller = renderer->gen_paint_controller();
  current_ecs->update(this->input_manager->get_current_input_state(), controller);
}
