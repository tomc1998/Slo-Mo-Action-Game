#include "sprite.hpp"

CompSprite::CompSprite(EntityId entity_id, TexHandle tex) {
  this->entity_id = entity_id;
  this->tex = tex;
}
