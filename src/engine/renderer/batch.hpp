#pragma once

#include "engine/renderer/vertex.hpp"
#include <vector>
#include <cstddef>

class PaintBuffer;

/** A batch of vertices, rendered with a texture */
class Batch {
  friend class PaintBuffer;
  friend class PaintController;

private:
  std::vector<Vertex> vertices;

public:
  u64 tex;

  Batch(u64 _tex);

  /** Buffer a list of vertices. This will perform a memcpy, so the vertices
   * can be disposed of afterwards. */
  void buffer(Vertex *vertices, size_t num_vertices);

  /** Clear this buffer */
  void clear();

  u64 size() const; 
};
