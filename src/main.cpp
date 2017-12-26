#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "engine/engine.hpp"
int main(int argc, char** argv) {

  Engine* engine = new Engine;
  engine->engine_go();
}
