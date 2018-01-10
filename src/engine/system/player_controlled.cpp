#include "engine/camera.hpp"
#include "engine/ecs.hpp"
#include "engine/input/input_state.hpp"
#include "globals.hpp"
#include "update_system.hpp"
#include <iostream>

class SystemPlayerControlled : public UpdateSystem {
public:
  void handle_components(Globals &globals) {
    const auto &ecs = globals.ecs;
    const auto &input_state = globals.input_state;
    const auto &camera = globals.camera;
    for (auto &p : ecs->comp_player_controlled) {
      if (p.life_left <= 0) {
        ecs->queue_entity_death(p.entity_id);
        continue;
      }
      CompGameEntity *ge = ecs->find_comp_game_entity_with_id(p.entity_id);

      p.state_change_timer++;

      if (p.get_state() != p.STATE_TELEPORTING) {
        if (input_state->rmb_down) {
          p.set_state(p.STATE_PRE_TELEPORT);
        } else if (input_state->lmb_down && !input_state->lmb_down_prev) {
          p.set_state(p.STATE_ATTACKING);
          // Figure out the angle to attack
          auto mouse_world_pos =
              input_state->mouse_pos + camera->get_top_left();
          auto player_world_pos = ge->pos;
          p.attack_angle = player_world_pos.angle_to(mouse_world_pos);
        }

        // Mouse button released? (teleport!)
        if (!input_state->rmb_down && input_state->rmb_down_prev) {
          p.set_state(p.STATE_TELEPORTING);
          p.teleport_pos = input_state->mouse_pos *
                               (camera->get_width() / camera->default_w) +
                           camera->get_top_left();
        }

        Vec2 *acc = &ge->acc;
        f32 force_to_apply = p.force_to_apply;
        f32 mass = ge->mass;
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
      } else {
        if (p.state_change_timer >= 200) {
          ge->pos = p.teleport_pos;
          p.set_state(p.STATE_NORMAL);
        }
      }

      // Check if attacking finished
      if (p.get_state() == p.STATE_ATTACKING) {
        if (p.state_change_timer >= 200) {
          p.set_state(p.STATE_NORMAL);
        }
      }

      camera->set_target_pos(ge->pos);
      break;
    }
  }
};
