#include "sprite.hpp"
#include "engine/texture.hpp"

CompSprite::CompSprite(EntityId entity_id, TexHandle tex) {
  this->entity_id = entity_id;
  this->tex = tex;
}
