#include <glad/glad.h>

#include <GLFW/glfw3.h>

#include "engine/camera.hpp"
#include "engine/renderer/renderer.hpp"
#include "engine/resource_manager.hpp"
#include "engine/vec.hpp"
#include <cassert>
#include <iostream>
#include <map>

Renderer::Renderer(f32 w, f32 h) {
  glGenBuffers(1, &dyn_vbo);

  // Compile the shader
  std::map<const GLchar *, GLuint> attrib_loc_bindings;
  attrib_loc_bindings["pos"] = Renderer::V_ATTR_POS_LOC;
  attrib_loc_bindings["col"] = Renderer::V_ATTR_COL_LOC;
  attrib_loc_bindings["uv"] = Renderer::V_ATTR_UV_LOC;
  std::map<const GLchar *, GLint *> uniform_loc_queries;
  uniform_loc_queries["proj_mat"] = &this->proj_mat_uniform_loc;
  uniform_loc_queries["tex"] = &this->tex_uniform_loc;
  shader = new Shader("assets/glsl/vert.glsl", "assets/glsl/frag.glsl",
                      attrib_loc_bindings, uniform_loc_queries);

  // Now that we've created the matrix & got shader uniform locations, we can
  // setup the shader uniforms
  glUseProgram(shader->program_id);
  glUniform1i(tex_uniform_loc, 0); // Bind tex to texture unit 0

  // Enable alpha blending
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  // Set background colour
  glClearColor(0.4, 0.4, 0.4, 1.0);
}

void Renderer::render(ResourceManager *res_manager, Camera *camera) {
  glUseProgram(shader->program_id);

  // Generate the projection matrix based on camera pos and zoom
  camera->gen_ortho_proj_mat(proj_mat);
  // Setup uniforms
  glUniformMatrix4fv(proj_mat_uniform_loc, 1, true, proj_mat);

  glBindBuffer(GL_ARRAY_BUFFER, dyn_vbo);
  glActiveTexture(GL_TEXTURE0 + 0);
  glEnableVertexAttribArray(Renderer::V_ATTR_POS_LOC);
  glEnableVertexAttribArray(Renderer::V_ATTR_COL_LOC);
  glEnableVertexAttribArray(Renderer::V_ATTR_UV_LOC);
  buffer.buffer_to_gl(Renderer::V_ATTR_POS_LOC, Renderer::V_ATTR_COL_LOC,
                      Renderer::V_ATTR_UV_LOC);

  // Loop through the triangles, and bind the right textures.
  u64 curr_ix = 0;
  for (const auto &b : buffer.b_buf) {
    res_manager->bind_cache_tex(b.tex);
    glDrawArrays(GL_TRIANGLES, curr_ix, b.size());
    curr_ix += b.size();
  }
}

void Renderer::clear_paint_buffer() { buffer.clear(); }

PaintController Renderer::gen_paint_controller(ResourceManager *rm,
                                               TexHandle white) {
  PaintController p(&buffer, rm, white);
  return p;
}
