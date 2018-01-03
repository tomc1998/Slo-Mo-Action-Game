#include "vec.hpp"
#include <cmath>

Vec2::Vec2(f32 _x, f32 _y) {
  x = _x;
  y = _y;
}

Vec2::Vec2() {
  x = 0.0;
  y = 0.0;
}

f32 Vec2::dot(const Vec2 vec) const { return vec.x * this->x + vec.y * this->y; }

Vec2 Vec2::sub(const Vec2 vec) const { return Vec2(this->x - vec.x, this->y - vec.y); }

Vec2 Vec2::add(const Vec2 vec) const { return Vec2(this->x + vec.x, this->y + vec.y); }

Vec2 Vec2::scl(const f32 k) const { return Vec2(this->x * k, this->y * k); }

f32 Vec2::len() const { return std::sqrt(this->x * this->x + this->y * this->y); }

f32 Vec2::len2() const { return (this->x * this->x + this->y * this->y); }

Vec2 Vec2::nor() const { return this->scl(1 / this->len()); }
