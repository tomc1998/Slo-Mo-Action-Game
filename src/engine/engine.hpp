#pragma once

#include "engine/camera.hpp"
#include "engine/input/input_manager.hpp"
#include "engine/renderer/renderer.hpp"
#include "engine/resource_manager.hpp"
#include "engine/screen.hpp"
#include "engine/system/globals.hpp"
#include <utility>
#include <vector>

class GLFWwindow;

/** Main engine, game code accesses engine through here. Shouldn't be
 * copied, & should exist for the full lifetime of the program. This will
 * NOT clean up any resources given to it (meaning that any resources given
 * should be removed before being freed, if they need to be freed). */
class Engine {
private:
  Renderer *renderer;
  Camera *camera;
  std::vector<std::pair<ECS *, Screen *>> screen_stack;
  /** Update the current state */
  void update();
  /** Paint the current state */
  void paint();
  InputManager *input_manager;
  ResourceManager *resource_manager;
  StandardTextures std_tex;

  static constexpr f32 FPS = 60.0;
  i32 max_updates_per_render = 10;
  i32 min_updates_per_render = 1;
  f32 updates_per_render = 10.0;
  bool slomo = false;

public:
  Engine();
  /** Push a screen to the screen stack.
   * The memory of screen will now be managed by the engine (if the screen is
   * popped the memory will be deleted) */
  void push_screen(Screen *screen);
  /** Pop a screen from the stack - this pointer may now be freed. */
  void pop_screen();
  /** Run the engine */
  void engine_go();

  GLFWwindow *window;
};
