#include "animation.hpp"
#include "engine/entity_id.hpp"
#include "engine/animation.hpp"
#include "engine/vec.hpp"

CompAnimation::CompAnimation(EntityId entity_id, AnimHandle ah, i32 length) {
  this->entity_id = entity_id;
  this->ah = ah;
  this->length = length;
  this->updates = 0;
}
