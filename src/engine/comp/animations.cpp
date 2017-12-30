#include "animations.hpp"
#include "engine/entity_id.hpp"
#include "engine/resource.hpp"
#include "engine/vec.hpp"

CompAnimations::CompAnimations(EntityId entity_id,
                             std::vector<Animation *> animations, ResHandle th) {
  this->entity_id = entity_id;
  this->animations = animations;
  this->animation_to_play = -1;
  this->updates = 0;
  this->th = th
}
