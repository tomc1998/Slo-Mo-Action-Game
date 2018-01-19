#include <glad/glad.h>

#include <GLFW/glfw3.h>

#include "engine/camera.hpp"
#include "engine/renderer/renderer.hpp"
#include "engine/resource_manager.hpp"
#include "shader.hpp"
#include "engine/canvas_size.hpp"
#include "engine/vec.hpp"
#include <map>
#include <iostream>

Renderer::Renderer(f32 w, f32 h) : hud_camera(Vec2(w/2.0, h/2.0), w, (w / h)) {
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

void Renderer::render_game(ResourceManager *res_manager, Camera *camera, i32 window_w, i32 window_h) {
  f32 proj_mat[16];

  // First off, set the viewport + letterbox
  f32 window_aspect = (f32) window_w / (f32) window_h;
  if (window_aspect < camera->get_aspect()) {
    // Letterbox top / bottom
    i32 spare_height = window_h - (i32)(1.0f/(camera->get_aspect()/(f32)window_w));
    glViewport(0, spare_height/2, window_w, window_h - spare_height); 
  }
  else {
    // Letterbox left / right
    i32 spare_width = window_w - (i32)((window_h*camera->get_aspect()));
    glViewport(spare_width/2, 0, window_w - spare_width, window_h); 
  }

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
  game_buffer.buffer_to_gl(Renderer::V_ATTR_POS_LOC, Renderer::V_ATTR_COL_LOC,
                           Renderer::V_ATTR_UV_LOC);

  // Loop through the triangles, and bind the right textures.
  u64 curr_ix = 0;
  for (const auto &b : game_buffer.b_buf) {
    res_manager->bind_cache_tex(b.tex);
    glDrawArrays(GL_TRIANGLES, curr_ix, b.size());
    curr_ix += b.size();
  }
  glDisableVertexAttribArray(Renderer::V_ATTR_POS_LOC);
  glDisableVertexAttribArray(Renderer::V_ATTR_COL_LOC);
  glDisableVertexAttribArray(Renderer::V_ATTR_UV_LOC);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindTexture(GL_TEXTURE_2D, 0);
  glUseProgram(0);
}

void Renderer::render_hud(ResourceManager *res_manager, i32 window_w, i32 window_h) {
  f32 proj_mat[16];

  // First off, set the viewport + letterbox
  f32 window_aspect = (f32) window_w / (f32) window_h;
  if (window_aspect < hud_camera.get_aspect()) {
    // Letterbox top / bottom
    i32 spare_height = window_h - (i32)(1.0f/(hud_camera.get_aspect()/(f32)window_w));
    glViewport(0, spare_height/2, window_w, window_h - spare_height); 
  }
  else {
    // Letterbox left / right
    i32 spare_width = window_w - (i32)((window_h*hud_camera.get_aspect()));
    glViewport(spare_width/2, 0, window_w - spare_width, window_h); 
  }

  // First off, set the viewport + letterbox
//  f32 window_aspect = (f32) window_h / (f32) window_w;
//  glViewport(0, 0, window_w, window_w*window_aspect);

  glUseProgram(shader->program_id);

  // Generate the projection matrix based on camera pos and zoom
  hud_camera.gen_ortho_proj_mat(proj_mat);
  // Setup uniforms
  glUniformMatrix4fv(proj_mat_uniform_loc, 1, true, proj_mat);

  glBindBuffer(GL_ARRAY_BUFFER, dyn_vbo);
  glActiveTexture(GL_TEXTURE0 + 0);
  glEnableVertexAttribArray(Renderer::V_ATTR_POS_LOC);
  glEnableVertexAttribArray(Renderer::V_ATTR_COL_LOC);
  glEnableVertexAttribArray(Renderer::V_ATTR_UV_LOC);
  hud_buffer.buffer_to_gl(Renderer::V_ATTR_POS_LOC, Renderer::V_ATTR_COL_LOC,
                          Renderer::V_ATTR_UV_LOC);

  // Loop through the triangles, and bind the right textures.
  u64 curr_ix = 0;
  for (const auto &b : hud_buffer.b_buf) {
    res_manager->bind_cache_tex(b.tex);
    glDrawArrays(GL_TRIANGLES, curr_ix, b.size());
    curr_ix += b.size();
  }
  glDisableVertexAttribArray(Renderer::V_ATTR_POS_LOC);
  glDisableVertexAttribArray(Renderer::V_ATTR_COL_LOC);
  glDisableVertexAttribArray(Renderer::V_ATTR_UV_LOC);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindTexture(GL_TEXTURE_2D, 0);
  glUseProgram(0);
}

void Renderer::clear_game_paint_buffer() { game_buffer.clear(); }
void Renderer::clear_hud_paint_buffer() { hud_buffer.clear(); }

PaintController Renderer::gen_paint_controller(ResourceManager *rm,
                                               TexHandle white) {
  PaintController p(&game_buffer, &hud_buffer, rm, white);
  return p;
}
