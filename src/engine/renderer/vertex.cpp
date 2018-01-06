#include "engine/renderer/vertex.hpp"

Vertex::Vertex(Vec2 _pos, f32 _layer, Color *_color, Vec2 _uv) {
  this->pos[0] = _pos.x;
  this->pos[1] = _pos.y;
  this->pos[2] = _layer;
  this->color[0] = _color->r;
  this->color[1] = _color->g;
  this->color[2] = _color->b;
  this->color[3] = _color->a;
  this->uv[0] = _uv.x;
  this->uv[1] = _uv.y;
}

Vertex::Vertex(Vec2 _pos, Color *_color, Vec2 _uv) {
  this->pos[0] = _pos.x;
  this->pos[1] = _pos.y;
  this->pos[2] = 0.0;
  this->color[0] = _color->r;
  this->color[1] = _color->g;
  this->color[2] = _color->b;
  this->color[3] = _color->a;
  this->uv[0] = _uv.x;
  this->uv[1] = _uv.y;
}

Vertex::Vertex() {
  this->pos[0] = 0.0;
  this->pos[1] = 0.0;
  this->pos[2] = 0.0;
  this->color[0] = 0.0;
  this->color[1] = 0.0;
  this->color[2] = 0.0;
  this->color[3] = 1.0;
  this->uv[0] = 0.0;
  this->uv[1] = 0.0;
}
