#include "globals.hpp"
#include "paint_system.hpp"
#include <cmath>

class SystemShadowRenderer : public PaintSystem {
public:
  void handle_components(Globals &globals) {
    auto &ecs = *globals.ecs;
    Color black = Color(0.0, 0.0, 0.0, 1.0);
    Texture *white = globals.paint_controller->get_white_tex();
    std::vector<Vertex> quads;
    for (const auto &p : ecs.comp_player_controlled) {
      const auto &ge = *ecs.find_comp_game_entity_with_id(p.entity_id);
      for (const auto &w : ecs.comp_wall) {
        // Cast shadows from the player's position to the wall
        quads.reserve(w.vertices.size() * 4);
        for (u32 ii = 0; ii < w.vertices.size(); ++ii) {
          const static f32 SHADOW_LEN = 2000.0;
          Vec2 curr_v = w.vertices[ii];
          Vec2 next_v = w.vertices[(ii + 1) % w.vertices.size()];
          // check if this is a back face. We only want to generate shadows on
          // back faces.
          // Since we can assume wall vertices are clockwise, we can just use
          // the cross product and check the sign.
          Vec2 w_v = (next_v - curr_v);
          Vec2 p_v = (ge.pos - curr_v);
          f32 cross = (w_v.x * p_v.y) - (w_v.y * p_v.x);
          if (cross < 0.0f) { continue; }

          Vec2 a = (curr_v - ge.pos) * SHADOW_LEN;
          Vec2 b = (next_v - ge.pos) * SHADOW_LEN;
          // generate a quad
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
        &quads[0], quads.size() / 4, globals.paint_controller->get_white_tex_handle());
  }
};
