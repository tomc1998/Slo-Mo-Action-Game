#pragma once
#include "vec.hpp"

/** Template 2row x 2col matrix class */
class Matrix2x2 {
public:
  f32 el[4];

  Matrix2x2();
  Matrix2x2(f32 a, f32 b, f32 c, f32 d);

  Vec2 mul(Vec2 v);
};
