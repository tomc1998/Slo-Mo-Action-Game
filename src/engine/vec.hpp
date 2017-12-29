#pragma once

/** Templated vector class. */
class Vec2 {
public:
  f32 x;
  f32 y;

  Vec2();
  Vec2(f32 _x, f32 _y);

  f32 dot_product(Vec2 vec);
  Vec2 subtract(Vec2 vec);
  Vec2 add(Vec2 vec);
  Vec2 mult(f32 k);
  f32 modulus_squared();
};
