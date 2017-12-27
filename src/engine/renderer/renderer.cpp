#include <glad/glad.h>

#include <GLFW/glfw3.h>

#include "engine/renderer/renderer.hpp"
#include "engine/vec.hpp"
#include <cassert>
#include <map>

/** Create an orthographic projection matrix, and store it in the given
 * destination. This will fill 16 f32s. */
void gen_ortho_proj_mat(f32 *dest, f32 l, f32 r, f32 t, f32 b, f32 n, f32 f) {
  dest[0] = 2.0 / (r - l);
  dest[1] = 0.0;
  dest[2] = 0.0;
  dest[3] = -(r + l) / (r - l);

  dest[4] = 0.0;
  dest[5] = 2.0 / (t - b);
  dest[6] = 0.0;
  dest[7] = -(t + b) / (t - b);

  dest[8] = 0.0;
  dest[9] = 0.0;
  dest[10] = -2.0 / (f - n);
  dest[11] = -(f + n) / (f - n);

  dest[12] = 0.0;
  dest[13] = 0.0;
  dest[14] = 0.0;
  dest[15] = 1.0;
}

void Renderer::setup_uniforms() {
  glUseProgram(shader->program_id);
  glUniformMatrix4fv(proj_mat_uniform_loc, 1, true, proj_mat);
}

Renderer::Renderer(f32 w, f32 h) {
  glGenBuffers(1, &dyn_vbo);

  // Compile the shader
  std::map<const GLchar *, GLuint> attrib_loc_bindings;
  attrib_loc_bindings["pos"] = Renderer::V_ATTR_POS_LOC;
  attrib_loc_bindings["col"] = Renderer::V_ATTR_COL_LOC;
  std::map<const GLchar *, GLint *> uniform_loc_queries;
  uniform_loc_queries["proj_mat"] = &this->proj_mat_uniform_loc;
  shader = new Shader("assets/glsl/vert.glsl", "assets/glsl/frag.glsl",
                      attrib_loc_bindings, uniform_loc_queries);

  // Create the orthographic projection matrix
  gen_ortho_proj_mat(proj_mat, 0.0, w, 0.0, h, -100.0, 100.0);

  // Now that we've created the matrix & got shader uniform locations, we can
  // setup the shader uniforms
  this->setup_uniforms();
}

void Renderer::render() {
  glBindBuffer(GL_ARRAY_BUFFER, dyn_vbo);
  glUseProgram(shader->program_id);
  glEnableVertexAttribArray(Renderer::V_ATTR_POS_LOC);
  glEnableVertexAttribArray(Renderer::V_ATTR_COL_LOC);
  buffer.buffer_to_gl(Renderer::V_ATTR_POS_LOC, Renderer::V_ATTR_COL_LOC);
  glDrawArrays(GL_TRIANGLES, 0, buffer.size());
}

void Renderer::clear_paint_buffer() { buffer.clear(); }

PaintController Renderer::gen_paint_controller() {
  PaintController p(&buffer);
  return p;
}
