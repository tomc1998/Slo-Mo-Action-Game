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
  Rect inset(EdgeInsets &insets) const;
  bool contains(Vec2 pos) const;
  f32 centre_x() const;
  f32 centre_y() const;
  Vec2 centre() const;
  /** y coord of rect top */
  f32 top() const;
  /** y coord of rect bottom */
  f32 bottom() const;
  /** x coord of rect left */
  f32 left() const;
  /** x coord of rect right */
  f32 right() const;

  Vec2 pos = Vec2(0.0, 0.0);
  Vec2 size = Vec2(0.0, 0.0);
};

/** Box constraints are essentially rectangles with the convention that a width
 * of -1 or height of -1 means the rectangle is unconstrained in that direction.
 */
typedef Rect BoxConstraints;
