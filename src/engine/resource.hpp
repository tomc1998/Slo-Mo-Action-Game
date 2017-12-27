#pragma once

class ResourceManager;

/** -1 indicates a 'null' resource handle */
typedef i32 ResHandle;

enum ResourceType { TEXTURE };

class Texture {
  friend class ResourceManager;
  /** The index of the cache texture */
  u64 cache_tex_ix;
  /** The uvs of the top left & bottom right of the texture in the cache */
  f32 uvs[4];
};

/** A resource, containing data about a resource type. Has an enum of the type,
 * then a union to contain this resource's actual data.*/
class Resource {
public:
  ResourceType type;
  union ResourceData {
    Texture texture; /** type == TEXTURE */
  } data;

  Resource(Texture t);
  Resource();
};
