#pragma once

#include "engine/renderer/vertex.hpp"
#include <cstddef>
#include <vector>

/** A buffer of batches. Paintcontrollers hold a reference to this, and add
 * batches. */
class PaintBuffer {
  private:
    std::vector<Vertex> v_buf;
  public:
    PaintBuffer();
    /** Buffer a list of vertices. This will perform a memcpy, so the vertices
     * can be disposed of afterwards. */
    void buffer(Vertex* vertices, size_t num_vertices);
};

