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

Rect Rect::intersect(Rect &r) const {
  f32 left = std::max(r.left(), this->left());
  f32 top = std::max(r.top(), this->top());
  f32 right = std::min(r.right(), this->right());
  f32 bottom = std::min(r.bottom(), this->bottom());
  return Rect(
      left, top, 
      std::max(0.0f, right - left),
      std::max(0.0f, bottom - top));
}

bool Rect::contains(Vec2 pos) const {
  Vec2 diff = pos - this->pos;
  return diff.x > 0.0 && diff.x < size.x && diff.y > 0.0 && diff.y < size.y;
}

f32 Rect::centre_x() const {
  return pos.x + size.y / 2.f;
}

f32 Rect::centre_y() const {
  return pos.y + size.y / 2.f;
}

Vec2 Rect::centre() const {
  return Vec2(centre_x(), centre_y());
}

f32 Rect::top() const {
  return pos.y;
}

f32 Rect::bottom() const {
  return pos.y + size.y;
}

f32 Rect::left() const {
  return pos.x;
}

f32 Rect::right() const {
  return pos.x + size.x;
}
