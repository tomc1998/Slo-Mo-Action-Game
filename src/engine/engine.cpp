#include "engine/ecs.hpp"
#include "engine/engine.hpp"
#include "engine/input/input_manager.hpp"
#include "engine/input/input_state.hpp"
#include "engine/screen.hpp"
#include <chrono>
#include <iostream>
#include <utility>
#ifdef __linux__
#include <unistd.h>
#elif _WIN32
#include <windows.h>
#else
#error "Platform not supported"
#endif

#include <glad/glad.h>

#include <GLFW/glfw3.h>

Engine::Engine() {
  glfwInit();
  this->window = glfwCreateWindow(800, 600, "Slo-Mo Action Game", NULL, NULL);
  glfwMakeContextCurrent(window);
  gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
  glfwSwapInterval(0);

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
    for (i32 ii = 0; ii < (int)this->updates_per_render; ii++) {
      this->input_manager->update_input();

      glClear(GL_COLOR_BUFFER_BIT);
      this->update();
    }

    auto frame_time_start = std::chrono::high_resolution_clock::now();

    this->paint();
    renderer->render();
    renderer->clear_paint_buffer();
    glfwSwapBuffers(this->window);

    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(
        std::chrono::high_resolution_clock::now() - frame_time_start);

    auto time_to_sleep_ms =
        1000.0 / (this->FPS) - ((f32)duration.count()) / 1000.0;

    if (time_to_sleep_ms > 0) {
#ifdef __linux__
      usleep(time_to_sleep_ms * 1000);
#elif _WIN32
      Sleep(time_to_sleep_ms);
#else
#error "Platform not supported"
#endif
    }

    if (glfwWindowShouldClose(this->window)) {
      break;
    }
  }
}

void Engine::update() {
  InputState *input_state = this->input_manager->get_current_input_state();
  if (input_state->slomo_down && !input_state->slomo_down_prev) {
    this->slomo = !this->slomo;
  }

  if (this->slomo &&
      this->updates_per_render > (f32)this->min_updates_per_render) {
    this->updates_per_render -= 0.5;
  }

  if (!this->slomo &&
      this->updates_per_render < (f32)this->max_updates_per_render) {
    this->updates_per_render += 0.5;
  }

  ECS *current_ecs = this->screen_stack.back().first;
  current_ecs->update(input_state);
}

void Engine::paint() {
  ECS *current_ecs = this->screen_stack.back().first;
  auto controller = renderer->gen_paint_controller();
  current_ecs->paint(this->input_manager->get_current_input_state(),
                     controller);
}
