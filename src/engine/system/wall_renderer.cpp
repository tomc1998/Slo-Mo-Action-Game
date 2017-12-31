#include "engine/color.hpp"
#include "engine/comp/game_entity.hpp"
#include "engine/ecs.hpp"
#include "engine/input/input_state.hpp"
#include "engine/renderer/paint_controller.hpp"
#include "engine/vec.hpp"
#include "paint_system.hpp"
#include <iostream>
#define _USE_MATH_DEFINES
#include <cmath>
#include <vector>

class SystemWallRenderer : public PaintSystem {

public:
  void handle_components(ECS *ecs, InputState *input_state,
                         PaintController *paint_controller) {
    const f32 EDGE_W = 8.0;
    Color white = Color(1.0, 1.0, 1.0, 1.0);
    for (const auto &w : ecs->comp_wall) {
      ResHandle edge_tex = w.edge_tex;

      // For this wall, calculate all the 'inner vertices'
      std::vector<Vec2> inner_verts;
      u32 n_verts = w.vertices.size();
      inner_verts.reserve(n_verts);
      for (u32 ii = 0; ii < n_verts; ++ii) {
        Vec2 curr_v = w.vertices[ii];
        Vec2 prev_v = w.vertices[(ii-1+n_verts)%n_verts];
        Vec2 next_v = w.vertices[(ii+1)%n_verts];
        // Given 2 vectors a and b, where a is the vector from prev_v to curr_v
        // and b is the vector from curr_v to next_v, there exists constants A
        // and B such that:
        //
        // normal(v) = the normal of vector v
        // A*a + EDGE_W*nor(normal(a)) = a + B*b + EDGE_W*nor(normal(b))
        // Finding these allows us to find the coordinates of the intersection,
        // which is the inner corner. We only need either one, so just split it
        // out into 2 equations in x & y, then solve for B via substitution:
        Vec2 a = curr_v.sub(prev_v);
        f32 a_len = a.modulus();
        Vec2 b = next_v.sub(curr_v);
        f32 b_len = b.modulus();
        Vec2 a_normal = Vec2(a.y, -a.x);
        Vec2 b_normal = Vec2(-b.y, b.x);

        f32 B = (EDGE_W * (a.dp(b)/b_len - a_len)) / b.dp(a_normal);

        inner_verts.push_back(curr_v.add(b.scl(B).add(b_normal.norm().scl(EDGE_W))));
      }

      for (const auto& vertex : w.vertices) {
        paint_controller->fill_rect(vertex.x, vertex.y, 1.0, 1.0, &white);
      }
      for (const auto& vertex : inner_verts) {
        paint_controller->fill_rect(vertex.x, vertex.y, 1.0, 1.0, &white);
      }
    }
  }
};
