#pragma once

#include "engine/color.hpp"
#include "engine/vec.hpp"
#include "engine/renderer/paint_controller.hpp"
#include "engine/renderer/paint_buffer.hpp"
#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Renderer {
  private:
    /** The handle of the main VBO used for rendering everything. This is
     * rebuffered every frame (hence the name 'dynamic vbo'). */
    GLuint dyn_vbo;
    PaintBuffer buffer;

  public:
    Renderer();
    /** Render a given paint buffer */
    void render(PaintBuffer* buffer);
    /** Generate a paint buffer. */
    PaintController* gen_paint_controller();
};
