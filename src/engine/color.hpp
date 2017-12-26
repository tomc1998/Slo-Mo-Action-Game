#pragma once
#include "engine/typedefs.hpp"

class Color {
  public:
    f32 r;
    f32 g;
    f32 b;
    f32 a;

    Color(f32 _r, f32 _g, f32 _b, f32 _a) {
      r = _r;
      g = _g;
      b = _b;
      a = _a;
    }

    /** Defaults to black */
    Color() {
      r = 0.0;
      g = 0.0;
      b = 0.0;
      a = 0.0;
    }
};
