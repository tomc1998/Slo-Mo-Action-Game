#include "animation.hpp"
#include "engine/entity_id.hpp"
#include "engine/animation.hpp"
#include "engine/vec.hpp"

CompAnimation::CompAnimation(EntityId entity_id, AnimHandle anim, FontHandle font, u32 length) {
  this->entity_id = entity_id;
  this->anim = anim;
  this->font = font;
  this->length = length;
  this->updates = 0;
}
