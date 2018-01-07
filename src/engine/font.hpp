#pragma once
#include "font_char.hpp"
#include "vec.hpp"
#include <sparsepp/spp.h>

class Font {
  spp::sparse_hash_map<char, FontChar>; 
  u32 line_height;
};
