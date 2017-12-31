#pragma once

/** Templated vector class. */
class Vec2 {
public:
  f32 x;
  f32 y;

  Vec2();
  Vec2(f32 _x, f32 _y);

  f32 dp(const Vec2 vec) const;
  Vec2 sub(const Vec2 vec) const;
  Vec2 add(const Vec2 vec) const;
  Vec2 scl(const f32 k) const;
  f32 modulus() const;
  f32 modulus_squared() const;
  Vec2 norm() const;
};
