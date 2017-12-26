#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "engine/renderer/renderer.hpp"
#include "engine/vec.hpp"

Renderer::Renderer() {
  glGenBuffers(1, &dyn_vbo);
}

PaintController* Renderer::gen_paint_controller() {
  PaintController* p = new PaintController(&buffer);
  return p;
}
