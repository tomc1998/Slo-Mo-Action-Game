#pragma once
#include "engine/color.hpp"
#include "engine/vec.hpp"

class Vertex {
public:
  f32 pos[3];
  f32 color[4];
  f32 uv[2];
  Vertex(Vec2 _pos, f32 _layer, Color *_color, Vec2 _uv);
  /** Default to layer 0 */
  Vertex(Vec2 _pos, Color *_color, Vec2 _uv);
  Vertex();
};
