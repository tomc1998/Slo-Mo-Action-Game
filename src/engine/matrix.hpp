#pragma once
#include "vec.hpp"

/** Template 2 x 2 matrix class 
 *
 * Matrix2x2(a, b, c, d) gives a matrix like this:
 *  [a, b]
 *  [c, d]
 *
 * */


class Matrix2x2 {
public:
  f32 el[4];

  Matrix2x2();
  Matrix2x2(f32 a, f32 b, f32 c, f32 d);

  Vec2 mul(Vec2 v);
};
