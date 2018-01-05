#include "engine/camera.hpp"
#include "engine/ecs.hpp"
#include "engine/input/input_state.hpp"
#include "update_system.hpp"
#include <iostream>

class SystemPlayerControlled : public UpdateSystem {
public:
  void handle_components(ECS *ecs, InputState *input_state, Camera *camera) {
    for (u32 ii = 0; ii < ecs->comp_game_entity.size(); ii++) {
      for (u32 jj = 0; jj < ecs->comp_player_controlled.size(); jj++) {
        if (ecs->comp_player_controlled[jj].entity_id !=
            ecs->comp_game_entity[ii].entity_id) {
          continue;
        }
        CompPlayerControlled* p = &ecs->comp_player_controlled[jj];

        if (input_state->lmb_down) {
          p->state = p->PRE_TELEPORT;
        } 
        Vec2 *acc = &ecs->comp_game_entity[ii].acc;
        f32 force_to_apply = ecs->comp_player_controlled[jj].force_to_apply;
        f32 mass = ecs->comp_game_entity[ii].mass;
        if (input_state->move_up >= 0) {
          acc->y = acc->y - force_to_apply / mass * input_state->move_up;
        }

        if (input_state->move_right >= 0) {
          acc->x = acc->x + force_to_apply / mass * input_state->move_right;
        }

        if (input_state->move_down >= 0) {
          acc->y = acc->y + force_to_apply / mass * input_state->move_down;
        }

        if (input_state->move_left >= 0) {
          acc->x = acc->x - force_to_apply / mass * input_state->move_left;
        }
        

        // Mouse button released
        if (!input_state->lmb_down && input_state->lmb_down_prev) {
          p->state = p->TELEPORTING;
        }

        camera->set_target_pos(ecs->comp_game_entity[ii].pos);
        break;
      }
    }
  }
};
