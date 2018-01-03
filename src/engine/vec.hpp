#pragma once

/** Templated vector class. */
class Vec2 {
public:
  f32 x;
  f32 y;

  Vec2();
  Vec2(f32 _x, f32 _y);

  f32 dot(const Vec2 vec) const;
  Vec2 sub(const Vec2 vec) const;
  Vec2 add(const Vec2 vec) const;
  Vec2 scl(const f32 k) const;
  f32 len() const;
  f32 len2() const;
  Vec2 nor() const;
  Vec2 operator+(Vec2 other) const;
  Vec2 operator+=(Vec2 other);
  Vec2 operator-(Vec2 other) const;
  Vec2 operator-=(Vec2 other);
  Vec2 operator*(f32 other) const;
  Vec2 operator*=(f32 other);
  Vec2 operator/(f32 other) const;
  Vec2 operator/=(f32 other);
};
