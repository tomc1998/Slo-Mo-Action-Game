#include "engine/renderer/batch.hpp"

Batch::Batch(u64 _tex) : tex(_tex) {}

void Batch::buffer(Vertex *_vertices, size_t num_vertices) {
  vertices.reserve(vertices.size() + num_vertices);
  for (size_t ii = 0; ii < num_vertices; ++ii) {
    vertices.push_back(_vertices[ii]);
  }
}

void Batch::clear() { vertices.clear(); }

u64 Batch::size() const { return vertices.size(); }
