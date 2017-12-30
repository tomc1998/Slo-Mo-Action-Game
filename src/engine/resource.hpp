#pragma once
#include "keyframe.hpp"
#include <vector>

class ResourceManager;

/** -1 indicates a 'null' resource handle */
typedef i32 ResHandle;

enum ResourceType { TEXTURE, ANIMATION };
enum InterpolationType { LINEAR };

class Texture {
public:
  /** The index of the cache texture */
  u64 cache_tex_ix;
  /** The uvs of the top left & bottom right of the texture in the cache */
  f32 uvs[4];
};

class Animation {
private:
  f32 linear_interpolation(f32 start_value, f32 end_value, i32 start_updates,
                           i32 end_updates, i32 curr_updates);

public:
  /** The texture handle of the sprite of the animation */
  ResHandle th;

  /** Vector of keyframes of the animation */

  /*
   * [0] = pos x
   * [1] = pos y
   * [2] = scale
   * [3] = rotation
   *
   * */
  std::vector<std::vector<Keyframe>> keyframes;

  std::vector<std::vector<InterpolationType>> interpolations;

  /** Gets the value of a certain attribute based on the amount of updates
   * through the animation you are
   * keyframe_type should be an integer from 0 to 3 representing the index in
   * the keyframes vector of the type of keyframe (e.g. 1 for pos y) */
  f32 get_interpolated_value(i32 updates, i32 keyframe_type);
};

/** A resource, containing data about a resource type. Has an enum of the type,
 * then a union to contain this resource's actual data.*/
class Resource {
public:
  ResourceType type;
  union ResourceData {
    Texture texture;     /** type == TEXTURE */
    Animation animation; /** type == ANIMATION */
  } data;

  Resource(Texture t);
  Resource(Animation a);
  Resource();
  ~Resource();
  Resource& operator=(const Resource& other);
};
