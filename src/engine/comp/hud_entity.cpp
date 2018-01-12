#include "engine/vec.hpp"
#include "engine/entity_id.hpp"
#include "hud_entity.hpp"

CompHudEntity::CompHudEntity(EntityId entity_id, Vec2 pos, Vec2 size) {
  this->entity_id = entity_id;
  this->pos = pos;
  this->size = size;
}
