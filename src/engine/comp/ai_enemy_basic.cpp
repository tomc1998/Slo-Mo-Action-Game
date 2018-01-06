#include "ai_enemy_basic.hpp"

CompAIEnemyBasic::CompAIEnemyBasic(EntityId entity_id) {
  this->entity_id = entity_id;
}

void CompAIEnemyBasic::set_state(u8 state) {
  this->state = state;
}

u8 CompAIEnemyBasic::get_state() {
  return state;
}
