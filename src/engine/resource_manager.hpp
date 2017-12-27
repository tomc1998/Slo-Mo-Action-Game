#pragma once
#include "engine/renderer/tex_cache.hpp"
#include "engine/resource.hpp"
#include "engine/typedefs.hpp"
#include <sparsepp/spp.h>

class ResourceManager {
private:
  ResHandle next_res_handle = 0;
  spp::sparse_hash_map<ResHandle, Resource> handle_map;

  TexCache tex_cache;

public:
  /** Load a texture & return a handle to access that texture */
  ResHandle load_texture(const char *path);
};
