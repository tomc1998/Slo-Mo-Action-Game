#pragma once
#include "anim_frame.hpp"
#include "keyframe.hpp"
#include "resource_defs.hpp"
#include <cstring>
#include <sparsepp/spp.h>
#include <utility>
#include <vector>

class ResourceManager;

/** Animation class that stores the animation of only 1 sprite, multiple
 * animations will be stored in the actual animation component */
class Animation {
private:
  /** Linearly interpolate between two values */
  f32 lerp(f32 start_value, f32 end_value, i32 start_updates, i32 end_updates,
           i32 curr_updates);
  spp::sparse_hash_map<u32, TexHandle> part_id_map;

public:
  /** Map of part IDs to their corresponding tex handle */

  /** Vectors of keyframes of the animation */
  std::vector<Keyframe> posx_keys;
  std::vector<Keyframe> posy_keys;
  std::vector<Keyframe> scale_keys;
  std::vector<Keyframe> rot_keys;

  u32 get_part_count();

  /** Returns an AnimFrame from the current timestamp
   *
   * @param[out] frames This should be a pointer to the start of enough allocated memory for all AnimFrames
   *
   * */
  void get_anim_frames(u32 updates, AnimFrame *frames);

  Animation();
  Animation(std::vector<TexHandle> texs);
};
