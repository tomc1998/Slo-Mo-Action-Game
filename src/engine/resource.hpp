#pragma once
#include "anim_frame.hpp"
#include "keyframe.hpp"
#include <cstring>
#include <utility>
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

/** Animation class that stores the animation of only 1 sprite, multiple
 * animations will be stored in the actual animation component */
class Animation {
private:
  f32 lerp(f32 start_value, f32 end_value, i32 start_updates, i32 end_updates,
          i32 curr_updates);

public:
  /** The texture handle of the sprite of the animation */
  ResHandle th;

  /** Vector of keyframes of the animation */

  
  std::vector<Keyframe> posx_keys;
  std::vector<Keyframe> posy_keys;
  std::vector<Keyframe> scale_keys;
  std::vector<Keyframe> rot_keys;

  std::vector<InterpolationType> posx_interps;
  std::vector<InterpolationType> posy_interps;
  std::vector<InterpolationType> scale_interps;
  std::vector<InterpolationType> rot_interps;
  
  AnimFrame get_anim_frame(i32 updates);

  /** Gets an animation frame based on the update timestamp */
};

/** A resource, containing data about a resource type. Has an enum of the type,
 * then a union to contain this resource's actual data.*/
class Resource {
public:
  ResourceType type;
  struct ResourceData {
    Texture texture;     /** type == TEXTURE */
    Animation animation; /** type == ANIMATION */
  } data;

  Resource(Texture t);
  Resource(Animation a);
  Resource();
  ~Resource();
  Resource &operator=(const Resource &other);
};
