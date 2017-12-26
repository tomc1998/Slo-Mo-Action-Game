#pragma once

/** Templated vector class. */
template <class T>
class Vec2 {
  public:
    T x;
    T y;

    Vec2(T _x, T _y);
    /** Create a zero vector */
    Vec2();
};
