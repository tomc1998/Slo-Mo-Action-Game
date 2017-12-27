#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "engine/engine.hpp"
#include "test_screen.hpp"
int main(int argc, char** argv) {

  
  Engine* engine = new Engine;

  TestScreen* test_screen = new TestScreen;
  engine->push_screen(test_screen);

  engine->engine_go();
}
