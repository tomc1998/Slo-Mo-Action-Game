#pragma once

#include "engine/renderer/vertex.hpp"
#include <cstddef>
#include <vector>

#include <GLFW/glfw3.h>

/** A buffer of batches. Paintcontrollers hold a reference to this, and add
 * batches. */
class PaintBuffer {
private:
  std::vector<Vertex> v_buf;

public:
  PaintBuffer();
  /** Buffer a list of vertices. This will perform a memcpy, so the vertices
   * can be disposed of afterwards. */
  void buffer(Vertex *vertices, size_t num_vertices);

  /** Clear this buffer */
  void clear();

  /** Buffer this data to the currently bound GL ARRAY BUFFER. Will
   * also call glVertexAttribPointer to set the location of the vertex
   * attributes, with the given indices.
   * @param[in] v_pos_index The index of the vertex position attribute
   *                        in the shader
   * @param[in] v_col_index The index of the colour attr in the shader
   */
  void buffer_to_gl(GLuint v_pos_index, GLuint v_col_index);

  u32 size();
};
