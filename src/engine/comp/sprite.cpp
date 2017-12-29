#include "engine/entity_id.hpp"
#include "engine/resource.hpp"
#include "engine/resource_manager.hpp"
#include "sprite.hpp"

CompSprite::CompSprite(EntityId entity_id, ResHandle th) {
  this->entity_id = entity_id;
  this->th = th;
}
