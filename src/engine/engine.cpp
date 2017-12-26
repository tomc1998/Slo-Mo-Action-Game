#include <utility>
#include "ecs.hpp"
#include "engine.hpp"
#include "screen.hpp"

Engine::Engine() {
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
  // TODO: Get input somehow
  //get_input()

  // Update the state
  this->update();

  //TODO: Render
  //render()
}

void Engine::update() {
  ECS* current_ecs = this->screen_stack.back().first;
  current_ecs->update();
}
