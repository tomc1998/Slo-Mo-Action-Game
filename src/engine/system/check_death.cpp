#include "globals.hpp"
#include "update_system.hpp"
#include <iostream>

class SystemCheckDeath : public UpdateSystem {

public:
  void handle_components(Globals &globals) {
    auto &ecs = *globals.ecs;
    for (auto &e : ecs.comp_player_killable) {
      if (e.life_left <= 0) {
        ecs.queue_entity_death(e.entity_id);
      } else if (e.inv_frames > 0) {
        e.inv_frames--;
      }
    }
    for (const auto &e : ecs.comp_player_controlled) {
      if (e.life_left <= 0) {
        ecs.queue_entity_death(e.entity_id);
      }
    }
  }
};
