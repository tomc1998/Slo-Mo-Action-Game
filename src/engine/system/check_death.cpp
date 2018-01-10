#include "update_system.hpp"
#include "globals.hpp"
#include <iostream>

class SystemCheckDeath : public UpdateSystem {

public:
  void handle_components(Globals &globals) {
    auto& ecs = *globals.ecs;
    for (const auto& e : ecs.comp_player_killable) {
      if (e.life_left <= 0) {
        ecs.queue_entity_death(e.entity_id);
      }
    }
    for (const auto& e : ecs.comp_player_controlled) {
      if (e.life_left <= 0) {
        ecs.queue_entity_death(e.entity_id);
      }
    }
  }
};

