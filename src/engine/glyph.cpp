#include "glyph.hpp"
#include <cstring>

Glyph::Glyph(f32 *uvs, u32 width, u32 height, i32 x_offset, i32 y_offset,
             i32 x_advance) {

  this->uvs[0] = uvs[0];
  this->uvs[1] = uvs[1];
  this->uvs[2] = uvs[2];
  this->uvs[3] = uvs[3];

  this->width = width;
  this->height = height;
  this->x_offset = x_offset;
  this->y_offset = y_offset;
  this->x_advance = x_advance;
}

Glyph::Glyph() {

  std::memset(this->uvs, 0.0, 4);
  this->width = 0;
  this->height = 0;
  this->x_offset = 0;
  this->y_offset = 0;
  this->x_advance = 0;

}
