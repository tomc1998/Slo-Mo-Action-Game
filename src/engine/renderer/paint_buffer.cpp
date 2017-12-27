#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cstddef>
#include <cassert>
#include "engine/renderer/paint_buffer.hpp"

PaintBuffer::PaintBuffer() {}

void PaintBuffer::buffer(Vertex* vertices, size_t num_vertices) {
  v_buf.reserve(v_buf.size() + num_vertices);
  for (size_t ii = 0; ii < num_vertices; ++ii) {
    v_buf.push_back(vertices[ii]);
  }
}

void PaintBuffer::clear() { v_buf.clear(); }

void PaintBuffer::buffer_to_gl(GLuint v_pos_index, GLuint v_col_index) {

  // Check that a buffer is actually bound
#ifndef NDEBUG
  GLint curr_buf;
  glGetIntegerv(GL_ARRAY_BUFFER_BINDING, &curr_buf);
  assert(curr_buf != 0);
#endif

  // Just straight buffer the whole thing, we're going to set the attrib
  // pointers as offsets to the Vertex object in memory anyway.
  size_t buf_size = v_buf.size() * sizeof(v_buf[0]);
  void* buf_data = &(v_buf[0]);
  glBufferData(GL_ARRAY_BUFFER, buf_size, buf_data, GL_DYNAMIC_DRAW);

  // Set attrib pointers
  GLvoid* pos_attr_offset = (GLvoid*) offsetof(Vertex,pos);
  GLvoid* col_attr_offset = (GLvoid*) offsetof(Vertex,color);
  glVertexAttribPointer(v_pos_index, 3, GL_FLOAT, GL_FALSE, sizeof(v_buf[0]), pos_attr_offset);
  glVertexAttribPointer(v_col_index, 4, GL_FLOAT, GL_FALSE, sizeof(v_buf[0]), col_attr_offset);
}


u32 PaintBuffer::size() { return v_buf.size(); }
