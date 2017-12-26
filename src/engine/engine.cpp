#include "engine.hpp"
#include "screen.hpp"

Engine::Engine() {
}

void Engine::push_screen(Screen* screen) {
  this->screen_stack.push_back(screen);
}

Screen* Engine::pop_screen() {
  Screen* back = screen_stack.back();
  screen_stack.pop_back();
  return back;
}
