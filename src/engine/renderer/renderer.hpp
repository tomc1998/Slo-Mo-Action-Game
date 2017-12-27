#pragma once

#include "engine/color.hpp"
#include "engine/vec.hpp"
#include "engine/renderer/paint_controller.hpp"
#include "engine/renderer/paint_buffer.hpp"
#include "engine/renderer/shader.hpp"
#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

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
    Shader* shader;

  public:
    Renderer();

    /** 
     * Render the internal paint buffer 
     *
     * @param needs_rebuffer[in] - If true, the data from the internal paint
     * buffer will be rebuffered to the VBO (with glbufferdata). If false, the
     * vbo will simply be re-rendered.
     */
    void render();

    /** Clear the internal paint buffer */
    void clear_paint_buffer();

    /** Generate a paint controller, pointing to this renderer's internal paint buffer. */
    PaintController* gen_paint_controller();

    /** The location of 'position' vertex attribute */
    static const GLuint V_ATTR_POS_LOC = 0;
    /** The location of 'color' vertex attribute */
    static const GLuint V_ATTR_COL_LOC = 1;
};
