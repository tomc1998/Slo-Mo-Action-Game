#include <iostream>
#include <GLFW/glfw3.h>

// Initialises GLFW and sets up a GL context given a screen width and
// height in the state pointer
GLFWwindow* init_glfw() {
  glfwInit();
  GLFWwindow* window = glfwCreateWindow(800, 600, "Slo-Mo Action Game", NULL, NULL);
  glfwMakeContextCurrent(window);
  return window;
}

int main(int argc, char** argv) {
  GLFWwindow* window = init_glfw();

  while(true) {
    // render
    glClear(GL_COLOR_BUFFER_BIT);
    glfwSwapBuffers(window);
    
    // Poll input
    glfwPollEvents();

    if (glfwWindowShouldClose(window)) {
      break;
    }
  }
}
