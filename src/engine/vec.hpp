#pragma once

/** Templated vector class. */
class Vec2 {
public:
  f32 x;
  f32 y;

  Vec2();
  Vec2(f32 _x, f32 _y);

  f32 dp(Vec2 vec);
  Vec2 sub(Vec2 vec);
  Vec2 add(Vec2 vec);
  Vec2 scl(f32 k);
  f32 modulus();
  f32 modulus_squared();
  Vec2 norm();
};
