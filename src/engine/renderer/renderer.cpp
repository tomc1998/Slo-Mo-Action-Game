#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cassert>
#include <map>
#include "engine/renderer/renderer.hpp"
#include "engine/vec.hpp"

Renderer::Renderer() {
  glGenBuffers(1, &dyn_vbo);
  std::map<const GLchar*, GLuint> attrib_loc_bindings;
  attrib_loc_bindings["pos"] = Renderer::V_ATTR_POS_LOC;
  attrib_loc_bindings["col"] = Renderer::V_ATTR_COL_LOC;
  shader = new Shader("assets/glsl/vert.glsl", "assets/glsl/frag.glsl", attrib_loc_bindings);
}

void Renderer::render() {
  glUseProgram(shader->program_id);
  glBindBuffer(GL_ARRAY_BUFFER, dyn_vbo);
  buffer.buffer_to_gl(Renderer::V_ATTR_POS_LOC, Renderer::V_ATTR_COL_LOC);
  glEnableVertexAttribArray(Renderer::V_ATTR_POS_LOC);
  glEnableVertexAttribArray(Renderer::V_ATTR_COL_LOC);
  glDrawArrays(GL_TRIANGLES, 0, buffer.size());
}

void Renderer::clear_paint_buffer() {
  buffer.clear();
}

PaintController* Renderer::gen_paint_controller() {
  PaintController* p = new PaintController(&buffer);
  return p;
}
