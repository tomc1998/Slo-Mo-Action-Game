#include "engine/renderer/paint_buffer.hpp"

PaintBuffer::PaintBuffer() {}
void PaintBuffer::buffer(Vertex* vertices, size_t num_vertices) {
  v_buf.reserve(v_buf.size() + num_vertices);
  for (size_t ii = 0; ii < num_vertices; ++ii) {
    v_buf.push_back(vertices[ii]);
  }
}

