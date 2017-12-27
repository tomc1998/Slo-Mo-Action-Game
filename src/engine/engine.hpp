#pragma once

#include <vector>
#include <utility>
#include "engine/screen.hpp"
#include "engine/renderer/renderer.hpp"
#include "engine/input/input_manager.hpp"

class GLFWwindow;

/** Main engine, game code accesses engine through here. Shouldn't be
 * copied, & should exist for the full lifetime of the program. This will
 * NOT clean up any resources given to it (meaning that any resources given
 * should be removed before being freed, if they need to be freed). */
class Engine {
  private:
    Renderer renderer;
    std::vector<std::pair<ECS*, Screen*>> screen_stack;
    /** Update the current state */
    void update();
    InputManager* input_manager;

  public:
    Engine();
    /** Push a screen to the screen stack. */
    /* The memory of screen will now be managed by the engine (if the screen is popped the memory will be deleted) */
    void push_screen(Screen* screen);
    /** Pop a screen from the stack - this pointer may now be freed. */
    void pop_screen();
    /** Run the engine */
    void engine_go();
    
    GLFWwindow* window;

};

