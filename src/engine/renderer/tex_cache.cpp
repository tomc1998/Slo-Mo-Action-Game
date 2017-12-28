#include "engine/renderer/tex_cache.hpp"
#include <cassert>
#include <cstdlib>
#include <cstring>
#include <iostream>

#include <glad/glad.h>

#include <GLFW/glfw3.h>

BinTreeNode::BinTreeNode(f32 _space[4]) {
  memcpy(space, _space, 4 * sizeof(f32));
}

BinTreeNode::~BinTreeNode() {
  if (l_child) {
    delete l_child;
  }
  if (r_child) {
    delete r_child;
  }
}

bool BinTreeNode::rect_for(ResHandle tex, f32 *rect) {
  if (tex_handle == tex) {
    memcpy(rect, space, 4 * sizeof(f32));
    return true;
  } else if (l_child && l_child->rect_for(tex, rect)) {
    return true;
  } else if (r_child && r_child->rect_for(tex, rect)) {
    return true;
  }
  return false;
}

bool BinTreeNode::pack_rect(ResHandle tex, f32 w, f32 h, f32 *dest) {
  if (!is_leaf()) {
    assert(l_child && r_child &&
           "Node in bin pack tree has a tex, but no children??");
    if (l_child->pack_rect(tex, w, h, dest)) {
      return true;
    }
    if (r_child->pack_rect(tex, w, h, dest)) {
      return true;
    }
    return false;
  }
  if (space[2] < w || space[3] < h) {
    return false; // don't have enough space in this leaf node to pack the rect
  }
  // Calculate the space to the right & below (left child) once this rect is
  // packed
  f32 r_space[4], l_space[4];
  l_space[0] = space[0];
  l_space[1] = space[1] + h;
  l_space[2] = space[2];
  l_space[3] = space[3] - h;
  r_space[0] = space[0] + w;
  r_space[1] = space[1];
  r_space[2] = space[2] - w;
  r_space[3] = space[3];

  // Create the child nodes & attach to this node
  l_child = new BinTreeNode(l_space);
  r_child = new BinTreeNode(r_space);

  // Update this node's space to the packed rect, & set the tex ID
  tex_handle = tex;
  space[2] = w;
  space[3] = h;

  memcpy(dest, space, 4 * sizeof(f32));
  return true;
}

bool BinTreeNode::is_leaf() { return (tex_handle == -1); }

bool TexCache::rect_for(ResHandle tex, f32 *rect) {
  for (auto &tree : bin_pack_trees) {
    if (tree.rect_for(tex, rect)) {
      return true;
    }
  }
  return false;
}

u64 TexCache::cache_tex(ResHandle tex, void *tex_data, u32 w, u32 h,
                        f32 *space) {
#ifndef NDEBUG
  // Check if cache textures will be big enough
  if (w > cache_tex_w || h > cache_tex_h) {
    std::cout << "Tried to buffer a texture that was too big for the texture\
      cache." << std::endl;
    assert(false);
  }
  // Check if tex handle is already used
  f32 tmp[4];
  if (rect_for(tex, tmp)) {
    std::cout << "Tried to buffer a texture with a resource ID which has\
      already been used."
              << std::endl;
    assert(false);
  }
#endif
  // Check if we can pack the rect in any of the existing bin pack trees
  u64 chosen_ix = 9999;
  BinTreeNode *chosen_tree = NULL;
  for (u32 ii = 0; ii < bin_pack_trees.size(); ++ii) {
    auto tree = bin_pack_trees[0];
    if (tree.pack_rect(tex, w, h, space)) {
      chosen_tree = &tree;
      chosen_ix = ii;
      break;
    }
  }
  if (!chosen_tree) {
    // We need to create a new cache texture, because all the existing ones are
    // full
    cache_textures.push_back(0);
    glGenTextures(1, &cache_textures.back());
    glBindTexture(GL_TEXTURE_2D, cache_textures.back());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    // Now we need to generate a massive texture to upload with glTexImage2d.
    // It doesn't matter what data is inside, but we need to allocate it.
    auto tex_buf = new char[cache_tex_w * cache_tex_h * 4];
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, cache_tex_w, cache_tex_h, 0,
                 GL_RGBA, GL_UNSIGNED_BYTE, tex_buf);
    delete[] tex_buf;
    // Now that we've created the texture memory, we need to add a bin packing
    // tree
    f32 new_node_space[] = {0.0, 0.0, 1.0, 1.0};
    bin_pack_trees.push_back(BinTreeNode(new_node_space));
    chosen_tree = &bin_pack_trees.back();
    chosen_ix = bin_pack_trees.size() - 1;
    chosen_tree->pack_rect(tex, (w/(f32)cache_tex_w), (h/(f32)cache_tex_h), space);
  }

  // Now buffer the texture
  i32 x = (i32)(space[0] * (f32)cache_tex_w);
  i32 y = (i32)(space[1] * (f32)cache_tex_h);
  glTexSubImage2D(GL_TEXTURE_2D, 0, x, y, w, h, GL_RGBA, GL_UNSIGNED_BYTE,
                  tex_data);

  // Finally, transform 'space' so that itcontains the UVs, not the w/h
  space[2] = space[0] + space[2];
  space[3] = space[1] + space[3];
  return chosen_ix;
}
