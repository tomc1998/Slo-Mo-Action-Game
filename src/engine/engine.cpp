#include "engine.hpp"
#include "screen.hpp"

Engine::Engine() {
}

void Engine::push_screen(Screen* screen) {
  this->screen_stack.push_back(screen);
}

Screen* Engine::pop_screen() {
  return this->screen_stack.pop_back();
}
