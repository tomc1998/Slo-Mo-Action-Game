#pragma once
#include "glyph.hpp"
#include "resource_defs.hpp"
#include "vec.hpp"
#include <sparsepp/spp.h>

class Font {
  /** The TexHandle of the actual font texture */
  Texture tex;
  /** Map of actual characters (e.g. 'a' or '3') to their respective FontChars
   */
  spp::sparse_hash_map<char, Glyph> char_map;
  /** How far down the cursor position */
  u32 line_height;

  i32 get_width_for_text(const char *text);
};
