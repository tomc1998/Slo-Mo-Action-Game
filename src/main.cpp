#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "engine/engine.hpp"
int main(int argc, char** argv) {

  Engine* engine = new Engine;
  while(true) {
    engine->engine_go();
    glClear(GL_COLOR_BUFFER_BIT);

    glfwSwapBuffers(engine->window);
    if (glfwWindowShouldClose(engine->window)){
      break;
    }
  }
}
