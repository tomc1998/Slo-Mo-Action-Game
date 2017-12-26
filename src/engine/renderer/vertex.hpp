#pragma once
#include "engine/vec.hpp"
#include "engine/color.hpp"

class Vertex {
  public:
  Vec2 pos;
  /** Basically a Z coordinate */
  f32 layer;
  Color color;
  Vertex(Vec2 _pos, f32 _layer, Color _color);
  /** Default to layer 0 */
  Vertex(Vec2 _pos, Color _color);
};


