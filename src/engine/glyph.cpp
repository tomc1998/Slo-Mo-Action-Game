#include "glyph.hpp"
#include <cstring>

Glyph::Glyph(f32 *uvs, u32 width, u32 height, i32 x_offset, i32 y_offset,
             i32 x_advance) {
  memcpy(this->uvs, uvs, 4*sizeof(f32));
  this->width = width;
  this->height = height;
  this->x_offset = x_offset;
  this->y_offset = y_offset;
  this->x_advance = x_advance;
}

Glyph::Glyph() {
  memset(this->uvs, 0.0f, 4);
  this->width = 0;
  this->height = 0;
  this->x_offset = 0;
  this->y_offset = 0;
  this->x_advance = 0;
}
