#include "engine/color.hpp"
#include "engine/comp/game_entity.hpp"
#include "engine/comp/player_controlled.hpp"
#include "engine/ecs.hpp"
#include "engine/input/input_state.hpp"
#include "engine/renderer/paint_controller.hpp"
#include "engine/vec.hpp"
#include "paint_system.hpp"
#include "globals.hpp"
#include <cmath>

/** Renders player effects, such as teleporting & attacking */
class SystemPlayerEffectRenderer : public PaintSystem {
public:
  void handle_components(Globals &globals) {
    const auto& ecs = globals.ecs;
    const auto& paint_controller = globals.paint_controller;
    const auto& input_state = globals.input_state;
    const auto& camera = globals.camera;
    Color white = Color(1.0, 1.0, 1.0, 1.0);
    Color black = Color(0.0, 0.0, 0.0, 1.0);
    Color red = Color(1.0, 0.0, 0.0, 1.0);
    for (u32 ii = 0; ii < ecs->comp_player_controlled.size(); ii++) {
      for (u32 jj = 0; jj < ecs->comp_game_entity.size(); jj++) {
        if (ecs->comp_player_controlled[ii].entity_id !=
            ecs->comp_game_entity[jj].entity_id) {
          continue;
        }
        CompGameEntity &ge = ecs->comp_game_entity[jj];
        CompPlayerControlled &p = ecs->comp_player_controlled[jj];

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
          const static u32 NUM_SEGMENTS = 2;
          const static f32 THICKNESS = 6.0;
          const static f32 START_RAD = 24.0;
          // Need this for rendering at the centre. Maybe rethink player anim rendering.
          const static Vec2 HALF_PLAYER = Vec2(8.0, 8.0);
          Texture *white = paint_controller->get_white_tex();
          Vertex quads[NUM_SEGMENTS * 4];
          f32 arc_start = p.attack_angle - M_PI / 3.0f;
          f32 seg_len = 2.0f * M_PI / 3.0f / (f32)NUM_SEGMENTS;
          // Pointer to the memory for the current quad
          Vertex *p_curr_quad = quads;
          f32 angle = arc_start;
          for (u32 ii = 0; ii < NUM_SEGMENTS; ++ii) {
            // TODO Cache previous vec, we're re-computing cos / sin
            Vec2 start_quad_vec = Vec2(cos(angle), sin(angle));
            Vec2 end_quad_vec =
                Vec2(cos(angle + seg_len), sin(angle + seg_len));
            p_curr_quad[0] = Vertex(ge.pos + HALF_PLAYER + start_quad_vec * START_RAD, &red,
                                    Vec2(white->uvs[0], white->uvs[1]));
            p_curr_quad[1] = Vertex(ge.pos + HALF_PLAYER + start_quad_vec * (START_RAD + THICKNESS), &red,
                                    Vec2(white->uvs[0], white->uvs[1]));
            p_curr_quad[2] = Vertex(ge.pos + HALF_PLAYER + end_quad_vec * (START_RAD + THICKNESS), &red,
                                    Vec2(white->uvs[0], white->uvs[1]));
            p_curr_quad[3] = Vertex(ge.pos + HALF_PLAYER + end_quad_vec * START_RAD, &red,
                                    Vec2(white->uvs[0], white->uvs[1]));
            p_curr_quad += 4;
            angle += seg_len;
          }
          paint_controller->draw_quads(
              quads, NUM_SEGMENTS,
              paint_controller->get_white_tex_handle());
        }

        break;
      }
    }
  }
};
