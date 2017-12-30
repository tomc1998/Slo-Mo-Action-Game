#include "animation.hpp"
#include "engine/entity_id.hpp"
#include "engine/resource.hpp"
#include "engine/vec.hpp"

CompAnimation::CompAnimation(EntityId entity_id,
                             std::vector<Animation *> animations) {
  this->entity_id = entity_id;
  this->animations = animations;
  this->animation_to_play = -1;
}
