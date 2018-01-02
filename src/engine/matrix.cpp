#include "vec.hpp"
#include "matrix.hpp"

Matrix2x2::Matrix2x2(f32 a, f32 b, f32 c, f32 d) {
  el[0] = a;
  el[1] = b;
  el[2] = c;
  el[3] = d;
}

Matrix2x2::Matrix2x2() {
  el[0] = 0.0;
  el[1] = 0.0;
  el[2] = 0.0;
  el[3] = 0.0;
}

Vec2 Matrix2x2::mul(Vec2 v) {
  return Vec2(el[0]*v.x + el[1]*v.y, el[2]*v.x + el[3]*v.y);
}
