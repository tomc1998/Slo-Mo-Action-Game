#include "vec.hpp"

template <class T>
Vec2<T>::Vec2(T _x, T _y) {
  this->x = x;
  this->y = y;
}

template <class T>
Vec2<T>::Vec2() {
  this->x = 0;
  this->y = 0;
}
