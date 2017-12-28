#pragma once

#include "engine/renderer/batch.hpp"
#include "engine/renderer/vertex.hpp"
#include <cstddef>
#include <vector>

#include <GLFW/glfw3.h>

/** A buffer of batches. Paintcontrollers hold a reference to this, and add
 * batches. */
class PaintBuffer {
  friend class Renderer;

private:
  std::vector<Batch> b_buf;

public:
  PaintBuffer();
  /** Add a batch to the buffer. */
  void buffer(Batch b);

  /** Clear this buffer */
  void clear();

  /** Buffer this data to the currently bound GL ARRAY BUFFER. Will
   * also call glVertexAttribPointer to set the location of the vertex
   * attributes, with the given indices.
   * @param[in] v_pos_index The index of the vertex position attribute
   *                        in the shader
   * @param[in] v_col_index The index of the colour attr in the shader
   *
   * This will buffer all the batches in order. You can just swap the texture
   * and make multiple glDrawArrays calls, with different offsets and lengths.
   */
  void buffer_to_gl(GLuint v_pos_index, GLuint v_col_index, GLuint v_uv_index);

  /** Calculate the total length of all the batches. Unlike most size()
   * functions, this actually involves some calculation, so cache the result if
   * you're reusing it.
   */
  u32 size();
};
