#include "common.hpp"

EdgeInsets::EdgeInsets(f32 top, f32 left, f32 right, f32 bottom)
    : top(top), left(left), right(right), bottom(bottom) {}

Rect::Rect(Vec2 pos, Vec2 size) : pos(pos), size(size) {}
Rect::Rect(f32 x, f32 y, f32 w, f32 h) : pos(x, y), size(w, h) {}
