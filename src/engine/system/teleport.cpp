#include "engine/camera.hpp"
#include "engine/comp/game_entity.hpp"
#include "engine/comp/player_controlled.hpp"
#include "engine/ecs.hpp"
#include "engine/input/input_state.hpp"
#include "engine/vec.hpp"
#include "update_system.hpp"

class SystemTeleport : public UpdateSystem {
public:
  void handle_components(ECS *ecs, InputState *input_state, Camera *camera) {
    for (u32 ii = 0; ii < ecs->comp_player_controlled.size(); ii++) {
      for (u32 jj = 0; jj < ecs->comp_game_entity.size(); jj++) {
        if (ecs->comp_player_controlled[ii].entity_id !=
            ecs->comp_game_entity[jj].entity_id) {
          continue;
        }

        if (ecs->comp_player_controlled[ii].state ==
            ecs->comp_player_controlled[ii].STATE_TELEPORTING) {
          CompPlayerControlled *p = &ecs->comp_player_controlled[ii];

          if (p->state_change_timer >= 200) {
            ecs->comp_game_entity[jj].pos = p->teleport_pos;
            p->state = p->STATE_NORMAL;
          }
        }
      }
    }
  }
};
