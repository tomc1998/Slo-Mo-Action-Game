#pragma once
#include "engine/vec.hpp"
#include "engine/color.hpp"

class Vertex {
  public:
    f32 pos[3];
    f32 color[4];
  Vertex(Vec2 _pos, f32 _layer, Color _color);
  /** Default to layer 0 */
  Vertex(Vec2 _pos, Color _color);
};


