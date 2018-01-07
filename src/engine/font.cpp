#include "font.hpp"

i32 Font::get_width_for_text(const char *text) {
  i32 width = 0;
  for (u32 ii=0; text[ii]!=0; ii++) {
    width += this->char_map[text[ii]].x_advance;
  }
  return width;
}

