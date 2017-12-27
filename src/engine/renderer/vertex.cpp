#include "engine/renderer/vertex.hpp"

Vertex::Vertex(Vec2 _pos, f32 _layer, Color *_color) {
  this->pos[0] = _pos.x;
  this->pos[1] = _pos.y;
  this->pos[2] = _layer;
  this->color[0] = _color->r;
  this->color[1] = _color->g;
  this->color[2] = _color->b;
  this->color[3] = _color->a;
}

Vertex::Vertex(Vec2 _pos, Color *_color) {
  this->pos[0] = _pos.x;
  this->pos[1] = _pos.y;
  this->pos[2] = 0.0;
  this->color[0] = _color->r;
  this->color[1] = _color->g;
  this->color[2] = _color->b;
  this->color[3] = _color->a;
}
