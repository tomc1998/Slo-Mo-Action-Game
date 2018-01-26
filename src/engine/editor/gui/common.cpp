#include "common.hpp"
#include <algorithm>

EdgeInsets::EdgeInsets(f32 top, f32 left, f32 right, f32 bottom)
    : top(top), left(left), right(right), bottom(bottom) {}

Rect::Rect(Vec2 pos, Vec2 size) : pos(pos), size(size) {}
Rect::Rect(f32 x, f32 y, f32 w, f32 h) : pos(x, y), size(w, h) {}

Rect Rect::inset(EdgeInsets &insets) const {
  return Rect(
      pos.x + insets.left, 
      pos.y + insets.top, 
      std::max(0.0f, size.x - insets.right - insets.left),
      std::max(0.0f, size.y - insets.bottom - insets.top));
}

bool Rect::contains(Vec2 pos) const {
  Vec2 diff = pos - this->pos;
  return diff.x > 0.0 && diff.x < size.x && diff.y > 0.0 && diff.y < size.y;
}
