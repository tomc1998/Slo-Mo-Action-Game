#include <glad/glad.h>

#include <GLFW/glfw3.h>

#include "engine/renderer/paint_buffer.hpp"
#include "engine/renderer/vertex.hpp"
#include <cassert>
#include <cstddef>
#include <vector>

PaintBuffer::PaintBuffer() {}

void PaintBuffer::buffer(Batch b) { b_buf.push_back(b); }

void PaintBuffer::clear() { b_buf.clear(); }

void PaintBuffer::buffer_to_gl(GLuint v_pos_index, GLuint v_col_index, GLuint v_uv_index) {

// Check that a buffer is actually bound
#ifndef NDEBUG
  GLint curr_buf;
  glGetIntegerv(GL_ARRAY_BUFFER_BINDING, &curr_buf);
  assert(curr_buf != 0);
#endif

  // Buffer all the batches in order
  u64 total_size = size();

  std::vector<Vertex> all_vertices;
  all_vertices.reserve(total_size);
  for (const auto &b : b_buf) {
    all_vertices.insert(all_vertices.begin(), b.vertices.begin(), b.vertices.end());
  }

  size_t buf_size = all_vertices.size() * sizeof(all_vertices[0]);
  void *buf_data = &(all_vertices[0]);
  glBufferData(GL_ARRAY_BUFFER, buf_size, buf_data, GL_DYNAMIC_DRAW);

  // Set attrib pointers
  GLvoid *pos_attr_offset = (GLvoid *)offsetof(Vertex, pos);
  GLvoid *col_attr_offset = (GLvoid *)offsetof(Vertex, color);
  GLvoid *uv_attr_offset = (GLvoid *)offsetof(Vertex, uv);
  glVertexAttribPointer(v_pos_index, 3, GL_FLOAT, GL_FALSE, sizeof(all_vertices[0]),
                        pos_attr_offset);
  glVertexAttribPointer(v_col_index, 4, GL_FLOAT, GL_FALSE, sizeof(all_vertices[0]),
                        col_attr_offset);
  glVertexAttribPointer(v_uv_index, 2, GL_FLOAT, GL_FALSE, sizeof(all_vertices[0]),
                        uv_attr_offset);
}

u32 PaintBuffer::size() { 
  u64 total_size = 0;
  for (const auto &b : b_buf) {
    total_size += b.vertices.size();
  }
  return total_size;
}
