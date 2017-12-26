#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "engine/renderer.hpp"
#include "engine/vec.hpp"
#include "engine/typedefs.hpp"

Vertex::Vertex(Vec2 _pos, f32 _layer, Color _color) {
  this->pos = _pos;
  this->layer = _layer;
  this->color = _color;
}

Vertex::Vertex(Vec2 _pos, Color _color) {
  this->pos = _pos;
  this->layer = 0.0;
  this->color = _color;
}

PaintBuffer::PaintBuffer() {}
void PaintBuffer::buffer(Vertex* vertices, size_t num_vertices) {
  v_buf.reserve(v_buf.size() + num_vertices);
  for (size_t ii = 0; ii < num_vertices; ++ii) {
    v_buf.push_back(vertices[ii]);
  }
}

Renderer::Renderer() {
}
