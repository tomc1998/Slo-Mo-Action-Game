#include "engine/camera.hpp"
#include "engine/color.hpp"
#include "engine/comp/game_entity.hpp"
#include "engine/comp/player_controlled.hpp"
#include "engine/ecs.hpp"
#include "engine/input/input_state.hpp"
#include "engine/renderer/paint_controller.hpp"
#include "engine/vec.hpp"
#include "paint_system.hpp"

/** Renders player effects, such as teleporting & attacking */
class SystemPlayerEffectRenderer : public PaintSystem {
public:
  void handle_components(ECS *ecs, InputState *input_state,
                         PaintController *paint_controller, Camera *camera) {
    Color white = Color(1.0, 1.0, 1.0, 1.0);
    Color black = Color(0.0, 0.0, 0.0, 1.0);
    Color red = Color(1.0, 0.0, 0.0, 1.0);
    for (u32 ii = 0; ii < ecs->comp_player_controlled.size(); ii++) {
      for (u32 jj = 0; jj < ecs->comp_game_entity.size(); jj++) {
        if (ecs->comp_player_controlled[ii].entity_id !=
            ecs->comp_game_entity[jj].entity_id) {
          continue;
        }
        CompGameEntity& ge = ecs->comp_game_entity[jj];
        CompPlayerControlled& p = ecs->comp_player_controlled[jj];

        // Render pre-teleport line from player to cursor
        if (p.get_state() == p.STATE_PRE_TELEPORT) {
          paint_controller->draw_line(ge.pos + Vec2(8.0, 8.0),
                                      input_state->rmb_drag.back() +
                                          camera->get_top_left(),
                                      2.0, &black, &white);
        }

        // Render attacking 'arc'
        else if (p.get_state() == p.STATE_ATTACKING) {
          // This is rendered in 2 quads forming a sort of arrow pointing in
          // the direction of p.attack_angle.
          paint_controller->draw_line(ge.pos + Vec2(8.0, 8.0),
                                      input_state->lmb_drag.back() +
                                          camera->get_top_left(),
                                      2.0, &red, &red);
        }

        break;
      }
    }
  }
};
