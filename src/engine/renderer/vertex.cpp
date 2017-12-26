#include "engine/renderer/vertex.hpp"

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


