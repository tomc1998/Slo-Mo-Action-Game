#include "vec.hpp"

Vec2::Vec2(f32 _x, f32 _y) {
  x = _x;
  y = _y;
}

Vec2::Vec2() {
  x = 0.0;
  y = 0.0;
}

f32 Vec2::dot_product(Vec2 vec) {
  return vec.x * this->x + vec.y * this->y;
}

Vec2 Vec2::subtract(Vec2 vec) {
  return Vec2(this->x - vec.x, this->y - vec.y);
}

Vec2 Vec2::add(Vec2 vec) {
  return Vec2(this->x + vec.x, this->y + vec.y);
}

Vec2 Vec2::mult(f32 k) {
  return Vec2(this->x * k, this->y * k);
}

f32 Vec2::modulus_squared() {
  return (this->x * this->x + this->y * this->y);
}
