#pragma once

#include <glad/glad.h>

#include <GLFW/glfw3.h>

#include "engine/color.hpp"
#include "engine/renderer/paint_buffer.hpp"
#include "engine/renderer/paint_controller.hpp"
#include "engine/renderer/shader.hpp"
#include "engine/vec.hpp"
#include <vector>

class ResourceManager;

/** Since this class will be alive for the existence of the engine, there is no
 * destructor cleanup, so creating this class effectively leaks memory.
 *
 * TODO: Add destructor to properly clean up memory.
 */
class Renderer {
private:
  /** The handle of the main VBO used for rendering everything. This is
   * rebuffered every frame (hence the name 'dynamic vbo'). */
  GLuint dyn_vbo;
  PaintBuffer buffer;

  /* Shader + uniform locations */
  Shader *shader;
  GLint proj_mat_uniform_loc;
  GLint tex_uniform_loc;

  f32 proj_mat[16];

  void setup_uniforms();

public:
  /** Initialise the renderer at the given viewport w / h */
  Renderer(f32 w, f32 h);

  /**
   * Render the internal paint buffer
   *
   * @param needs_rebuffer[in] - If true, the data from the internal paint
   * buffer will be rebuffered to the VBO (with glbufferdata). If false, the
   * vbo will simply be re-rendered.
   */
  void render(ResourceManager* res_manager);

  /** Clear the internal paint buffer */
  void clear_paint_buffer();

  /** Generate a paint controller, pointing to this renderer's internal paint
   * buffer. Provide a texture to use for coloured (non-textured) drawing -
   * this should be a white square for normal results.*/
  PaintController gen_paint_controller(ResourceManager *rm, ResHandle white);

  /** The location of 'position' vertex attribute */
  static const GLuint V_ATTR_POS_LOC = 0;
  /** The location of 'color' vertex attribute */
  static const GLuint V_ATTR_COL_LOC = 1;
  /** The location of 'uv' vertex attribute */
  static const GLuint V_ATTR_UV_LOC = 2;

  /** The location of the 'tex' sampler uniform */
  static const GLuint V_ATTR_TEX_LOC = 0;
};
