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
      auto& ge = *ecs->find_comp_game_entity_with_id(p.entity_id);

      p.state_change_timer++;

      if (p.get_state() != p.STATE_TELEPORTING) {
        if (input_state->rmb_down) {
          p.set_state(p.STATE_PRE_TELEPORT);
        } else if (input_state->lmb_down && !input_state->lmb_down_prev) {
          p.set_state(p.STATE_ATTACKING);
          // Figure out the angle to attack
          auto mouse_world_pos =
              input_state->mouse_pos + camera->get_top_left();
          auto player_world_pos = ge.pos;
          p.attack_angle = player_world_pos.angle_to(mouse_world_pos);
        }

        // Mouse button released? (teleport!)
        if (!input_state->rmb_down && input_state->rmb_down_prev) {
          p.set_state(p.STATE_TELEPORTING);
          p.teleport_pos = input_state->mouse_pos *
                               (camera->get_width() / camera->default_w) +
                           camera->get_top_left();
        }

        Vec2 *acc = &ge.acc;
        f32 force_to_apply = p.force_to_apply;
        f32 mass = ge.mass;
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
          ge.pos = p.teleport_pos;
          p.set_state(p.STATE_NORMAL);
        }
      }

      if (p.get_state() == p.STATE_ATTACKING) {
        if (p.state_change_timer >= 200) {
          p.set_state(p.STATE_NORMAL);
        } else {
          // Check collisions with player killables
          for (auto &pk : ecs->comp_player_killable) {
            const auto &pk_ge = *ecs->find_comp_game_entity_with_id(pk.entity_id);
            // First check we're at the right distance to be hit, then check
            // we're at the right angle
            const auto min_dis = (pk_ge.pos - ge.pos).len() - pk.hit_rad;
            const auto max_dis = (pk_ge.pos - ge.pos).len() + pk.hit_rad;
            if (!(min_dis < p.ATTACK_ARC_MAX_DIS && max_dis > p.ATTACK_ARC_MIN_DIS)) {
              std::cout << "Hello0" << std::endl;
              continue;
            }
            // TODO: For angle checking we don't take into account the hit rad
            // of the player killable. this collision is already a little
            // janky, however, and it FEELS good right now, which is the
            // important thing.
            // Check angle, adding 4pi to prevent any fuckery with goin 'full circle'
            const auto angle = ge.pos.angle_to(pk_ge.pos) + 4.0f*M_PI;
            const auto angle_diff = abs(angle - (p.attack_angle + 4.0f*M_PI));
            if (angle_diff > p.ATTACK_ARC_LEN/4.0f) {
              std::cout << "Hello1" << std::endl;
              continue;
            }
            pk.life_left -= 1;
          }
        }
      }

      camera->set_target_pos(ge.pos);
      break;
    }
  }
};
