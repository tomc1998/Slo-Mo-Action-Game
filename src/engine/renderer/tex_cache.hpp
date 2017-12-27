#pragma once

#include <glad/glad.h>

#include <GLFW/glfw3.h>

#include "engine/resource.hpp"
#include <vector>

class BinTreeNode {
public:
  BinTreeNode *l_child = NULL;
  BinTreeNode *r_child = NULL;
  /** The space (X,Y,W,H) used up by this bin packing binary tree node */
  f32 space[4];
  /** The texture stored in this node, or -1 if this node is currently empty */
  ResHandle tex_handle;

  BinTreeNode(f32 _space[4]);
  ~BinTreeNode();

  /**
   * @param[out] rect The output rectangle found
   * @return true if a rectangle was fonud, false otherwise
   */
  bool rect_for(ResHandle tex, f32 *rect);

  /** Pack a rectangle into this tree. Returns true if the rectangle was
   * successfully packed.
   * @param[out] dest If there was enough space, this will contain the location
   * of the texture as UV coordinates, X, Y, W, H.
   */
  bool pack_rect(ResHandle tex, f32 w, f32 h, f32 *dest);

  /** Returns true if this node is a leaf node */
  bool is_leaf();
};

/** A class for caching textures to the GPU. */
class TexCache {
private:
  /** A list of binary trees, each corresponding to a cache texture */
  std::vector<BinTreeNode> bin_pack_trees;

  /** The size of the cache textures */
  const u32 cache_tex_w = 2048, cache_tex_h = 2048;

public:
  /** The textures used */
  std::vector<GLuint> cache_textures;

  /** Cache some texture data.
   *
   * This will assert false with an error message if the given texture is larger
   * than
   * the maximum cache texture size.
   *
   * This will assert false with an error message if the texture handle T is
   * already being used.
   *
   * These assertions will only be checked if NDEBUG is not defined, otherwise
   * this will cause undefined behaviour.
   *
   * Any GL errors will assert false and output the error code.
   *
   * tex_data is a 4-channel byte array, 8 bits per channel, RGBA (conveniently
   * what is output by stb_image).
   *
   * @param[out] space The UV rectangle this was cached into
   * @return The index of the cache texture this was cached into
   */
  u64 cache_tex(ResHandle t, void *tex_data, u32 w, u32 h, f32 *space);

  /**
   * @param[out] rect The output rectangle found
   * @return true if a rectangle was found, false otherwise
   */
  bool rect_for(ResHandle tex, f32 *rect);
};
