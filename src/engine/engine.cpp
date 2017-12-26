#include "engine.hpp"
#include "screen.hpp"

Engine::Engine() {
}

void Engine::push_screen(Screen* screen) {
  this->screen_stack.push_back(screen);
}

void Engine::pop_screen() {
  Screen* back = screen_stack.back();
  screen_stack.pop_back();
}

void Engine::engine_go() {
  // TODO: Get input somehow
  //get_input()

  // Update the state
  this->update();

  //TODO: Render
  //render()
}

void Engine::update() {
  current_ecs = this->screen_stack.back.first;
  current_ecs.update();
}
