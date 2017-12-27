#include "engine/resource.hpp"

Resource::Resource(Texture t) {
  type = ResourceType::TEXTURE;
  data.texture = t;
}

Resource::Resource() {}
