#pragma once

#include "engine/vec.hpp"

/** Represents some edge insets, for padding and the like. */
class EdgeInsets {
public:
  EdgeInsets(f32 top, f32 left, f32 right, f32 bottom);
  f32 top = 0.0;
  f32 left = 0.0;
  f32 right = 0.0;
  f32 bottom = 0.0;
};

class Rect {
public:
  Rect(Vec2 pos, Vec2 size);
  Rect(f32 x, f32 y, f32 w, f32 h);

  /** Generate a new rectangle with the given. Minimum rectangle size will
   * always be (0,0). */
  Rect inset(EdgeInsets &insets);

  Vec2 pos = Vec2(0.0, 0.0);
  Vec2 size = Vec2(0.0, 0.0);
};