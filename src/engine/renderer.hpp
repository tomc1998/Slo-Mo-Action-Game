#pragma once
#include "engine/color.hpp"
#include "engine/vec.hpp"
#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Vertex {
  public:
  Vec2 pos;
  /** Basically a Z coordinate */
  f32 layer;
  Color color;
  Vertex(Vec2 _pos, f32 _layer, Color _color);
  /** Default to layer 0 */
  Vertex(Vec2 _pos, Color _color);
};

/** A buffer of batches. Paintcontrollers hold a reference to this, and add
 * batches. */
class PaintBuffer {
  private:
    std::vector<Vertex> v_buf;
    PaintBuffer();
  public:
    /** Buffer a list of vertices. This will perform a memcpy, so the vertices
     * can be disposed of afterwards. */
    void buffer(Vertex* vertices, size_t num_vertices);
};

class Renderer {
  private:
    /** The handle of the main VBO used for rendering everything. This is
     * rebuffered every frame (hence the name 'dynamic vbo'). */
    GLuint dyn_vbo;

  public:
    Renderer();
};
