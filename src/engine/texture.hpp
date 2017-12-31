#pragma once
#include "resource_defs.hpp"

/** -1 indicates a 'null' tex handle */

class Texture {
public:
  /** The index of the cache texture */
  u64 cache_tex_ix;
  /** The uvs of the top left & bottom right of the texture in the cache */
  f32 uvs[4];
};
