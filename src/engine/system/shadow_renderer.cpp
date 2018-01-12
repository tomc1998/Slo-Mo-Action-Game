#include "globals.hpp"
#include "paint_system.hpp"
#include <cmath>
#include <algorithm>

class SystemShadowRenderer : public PaintSystem {
public:
  void handle_components(Globals &globals) {
    auto &ecs = *globals.ecs;
    Color black = Color(0.0, 0.0, 0.0, 1.0);
    Texture *white = globals.paint_controller->get_white_tex();
    Texture *penumbra =
        globals.paint_controller->get_tex_for_handle(globals.std_tex->penumbra);
    std::vector<Vertex> quads;
    for (const auto &p : ecs.comp_player_controlled) {
      const auto &ge = *ecs.find_comp_game_entity_with_id(p.entity_id);
      for (const auto &w : ecs.comp_wall) {
        // Cast shadows from the player's position to the wall
        quads.reserve(w.vertices.size() * 12);
        // First, get a list of backfaces
        // TODO: Better data structure than array of bools? Not too cache
        // friendly!
        std::vector<bool> is_backface;
        for (u32 ii = 0; ii < w.vertices.size(); ++ii) {
          Vec2 curr_v = w.vertices[ii];
          Vec2 next_v = w.vertices[(ii + 1) % w.vertices.size()];
          Vec2 w_v = (next_v - curr_v);
          Vec2 p_v = (ge.pos - curr_v);
          f32 cross = (w_v.x * p_v.y) - (w_v.y * p_v.x);
          if (cross < 0.0f) {
            is_backface.push_back(false);
          } else {
            is_backface.push_back(true);
          }
        }

        for (u32 ii = 0; ii < w.vertices.size(); ++ii) {
          if (!is_backface[ii]) {
            continue;
          }
          const static f32 SHADOW_LEN = 1000.0;
          // How wide is the soft part of the shadow?
          Vec2 curr_v = w.vertices[ii];
          Vec2 next_v = w.vertices[(ii + 1) % w.vertices.size()];
          bool is_prev_backface = is_backface[(ii - 1) % is_backface.size()];
          bool is_next_backface = is_backface[(ii + 1) % is_backface.size()];

          // Generate the shadow. If the previous / next is not a backface,
          // then draw a penumbra.
          Vec2 a = (curr_v - ge.pos).nor() * SHADOW_LEN;
          Vec2 b = (next_v - ge.pos).nor() * SHADOW_LEN;
          if (!is_prev_backface) { // penumbra on a
            f32 dis_to_p = (curr_v - ge.pos).len();
            f32 soft_angle = std::min((M_PI/8.0f)*(50.0/dis_to_p), M_PI/8.0f);
            f32 angle_a = atan2(a.y, a.x);
            f32 angle_a_soft = angle_a - soft_angle / 2.0f;
            Vec2 a_soft;
            a_soft.x = cos(angle_a_soft) * SHADOW_LEN;
            a_soft.y = sin(angle_a_soft) * SHADOW_LEN;
            // Draw a penumbra
            quads.push_back(Vertex(curr_v, &black,
                                   Vec2(penumbra->uvs[0], penumbra->uvs[3])));
            quads.push_back(Vertex(curr_v + a_soft, &black,
                                   Vec2(penumbra->uvs[0], penumbra->uvs[1])));
            quads.push_back(Vertex(curr_v + a, &black,
                                   Vec2(penumbra->uvs[2], penumbra->uvs[1])));
            quads.push_back(Vertex(curr_v, &black,
                                   Vec2(penumbra->uvs[0], penumbra->uvs[3])));
          }
          if (!is_next_backface) { // penumbra on b
            f32 dis_to_p = (curr_v - ge.pos).len();
            f32 soft_angle = std::min((M_PI/8.0f)*(50.0/dis_to_p), M_PI/8.0f);
            f32 angle_b = atan2(b.y, b.x);
            f32 angle_b_soft = angle_b + soft_angle / 2.0f;
            Vec2 b_soft;
            b_soft.x = cos(angle_b_soft) * SHADOW_LEN;
            b_soft.y = sin(angle_b_soft) * SHADOW_LEN;
            // Draw a penumbra
            quads.push_back(Vertex(next_v, &black,
                                   Vec2(penumbra->uvs[0], penumbra->uvs[3])));
            quads.push_back(Vertex(next_v + b_soft, &black,
                                   Vec2(penumbra->uvs[0], penumbra->uvs[1])));
            quads.push_back(Vertex(next_v + b, &black,
                                   Vec2(penumbra->uvs[2], penumbra->uvs[1])));
            quads.push_back(Vertex(next_v, &black,
                                   Vec2(penumbra->uvs[0], penumbra->uvs[3])));
          }

          // generate a quad for the full (hard) shadow
          quads.push_back(
              Vertex(curr_v, &black, Vec2(white->uvs[0], white->uvs[1])));
          quads.push_back(
              Vertex(next_v, &black, Vec2(white->uvs[0], white->uvs[1])));
          quads.push_back(
              Vertex(next_v + b, &black, Vec2(white->uvs[0], white->uvs[1])));
          quads.push_back(
              Vertex(curr_v + a, &black, Vec2(white->uvs[0], white->uvs[1])));
        }
      }
    }
    globals.paint_controller->draw_quads(
        &quads[0], quads.size() / 4,
        globals.paint_controller->get_white_tex_handle());
  }
};
