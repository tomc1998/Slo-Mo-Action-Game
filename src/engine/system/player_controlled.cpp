#include "system.hpp"
#include "engine/input/input_state.hpp"
#include "engine/ecs.hpp"

class SystemPlayerControlled: public System {
  public:
    void handle_components(ECS* ecs, InputState* input_state ) {
      for (u32 ii=0; ii < ecs->comp_game_entity.size(); ii++) {
        for (u32 jj=0; jj < ecs->comp_player_controlled.size(); ii++) {
          if (ecs->comp_player_controlled[jj].entity_id == ecs->comp_game_entity[ii].entity_id) {
            if (input_state->move_up >= 0) {
              ecs->comp_game_entity[ii].acc.y = ecs->comp_game_entity[ii].acc.y - ecs->comp_player_controlled[jj].force_to_apply/ecs->comp_game_entity[ii].mass * input_state->move_up;
            }

            if (input_state->move_right >= 0) {
              ecs->comp_game_entity[ii].acc.x = ecs->comp_game_entity[ii].acc.x + ecs->comp_player_controlled[jj].force_to_apply/ecs->comp_game_entity[ii].mass * input_state->move_right;
            }

            if (input_state->move_down >= 0) {
              ecs->comp_game_entity[ii].acc.y = ecs->comp_game_entity[ii].acc.y + ecs->comp_player_controlled[jj].force_to_apply/ecs->comp_game_entity[ii].mass * input_state->move_down;
            }

            if (input_state->move_left >= 0) {
              ecs->comp_game_entity[ii].acc.x = ecs->comp_game_entity[ii].acc.y - ecs->comp_player_controlled[jj].force_to_apply/ecs->comp_game_entity[ii].mass * input_state->move_left;
            }
          }

        } 
      }
    }
};
