#include "animation.hpp"
#include "engine/entity_id.hpp"

CompAnimation::CompAnimation() {}

CompAnimation::CompAnimation(EntityId entity_id, AnimHandle anim, u32 length) {
  this->entity_id = entity_id;
  this->anim = anim;
  this->length = length;
  this->updates = 0;
}
