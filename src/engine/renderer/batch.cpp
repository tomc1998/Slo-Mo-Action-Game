#include "engine/renderer/batch.hpp"

Batch::Batch(u64 _tex) : tex(_tex) {}

void Batch::buffer(Vertex *_vertices, size_t num_vertices) {
  vertices.insert(vertices.end(), _vertices, _vertices + num_vertices);
}

void Batch::clear() { vertices.clear(); }

u64 Batch::size() const { return vertices.size(); }
