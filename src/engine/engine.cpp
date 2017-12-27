#include "engine/ecs.hpp"
#include "engine/engine.hpp"
#include "engine/input/input_manager.hpp"
#include "engine/screen.hpp"
#include <chrono>
#include <iostream>
#include <utility>
#ifdef __linux__
#include <unistd.h>
#elif _WIN32
#include <windows.h>
#endif

#include <glad/glad.h>

#include <GLFW/glfw3.h>

Engine::Engine() {
  glfwInit();
  this->window = glfwCreateWindow(800, 600, "Slo-Mo Action Game", NULL, NULL);
  glfwMakeContextCurrent(window);
  gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

  this->renderer = new Renderer(800.0, 600.0);
  this->input_manager = new InputManager(this->window);
}

void Engine::push_screen(Screen *screen) {
  ECS *ecs = new ECS();
  screen->init(ecs);
  this->screen_stack.push_back(std::pair<ECS *, Screen *>(ecs, screen));
}

void Engine::pop_screen() {
  std::pair<ECS *, Screen *> back = screen_stack.back();
  delete back.first;
  delete back.second;
  screen_stack.pop_back();
}

void Engine::engine_go() {
  while (true) {
    this->input_manager->update_input();

    glClear(GL_COLOR_BUFFER_BIT);
    this->update();

    auto frame_time_start = std::chrono::high_resolution_clock::now();

    renderer->render();
    renderer->clear_paint_buffer();

    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(
        frame_time_start - std::chrono::high_resolution_clock::now());

    auto time_to_sleep_ms = 1000.0 / (this->FPS) - duration.count();
    
    if (time_to_sleep_ms > 0) {
#ifdef __linux__
      usleep(time_to_sleep_ms * 1000);
#elif _WIN32
      Sleep(time_to_sleep_ms);
#else
#error "Platform not supported"
#endif
    }


    glfwSwapBuffers(this->window);
    if (glfwWindowShouldClose(this->window)) {
      break;
    }
  }
}

void Engine::update() {
  ECS *current_ecs = this->screen_stack.back().first;
  auto controller = renderer->gen_paint_controller();
  current_ecs->update(this->input_manager->get_current_input_state());
  current_ecs->paint(this->input_manager->get_current_input_state(),
                     controller);
}
