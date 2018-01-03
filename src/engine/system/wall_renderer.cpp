#include "engine/color.hpp"
#include "engine/comp/game_entity.hpp"
#include "engine/camera.hpp"
#include "engine/ecs.hpp"
#include "engine/input/input_state.hpp"
#include "engine/renderer/paint_controller.hpp"
#include "engine/vec.hpp"
#include "paint_system.hpp"
#define _USE_MATH_DEFINES
#include <cmath>
#include <vector>

class SystemWallRenderer : public PaintSystem {

public:
  void handle_components(ECS *ecs, InputState *input_state,
                         PaintController *paint_controller, Camera *camera) {
    const f32 EDGE_W = 16.0;
    const f32 SEG_LEN = 16.0;
    Color white = Color(1.0, 1.0, 1.0, 1.0);
    for (const auto &w : ecs->comp_wall) {
      TexHandle edge_tex = w.edge_tex;
      const auto &t = paint_controller->get_tex_for_handle(edge_tex);

      // For this wall, calculate all the 'inner vertices'
      std::vector<Vec2> inner_verts;
      u32 n_verts = w.vertices.size();
      inner_verts.reserve(n_verts);
      for (u32 ii = 0; ii < n_verts; ++ii) {
        Vec2 curr_v = w.vertices[ii];
        Vec2 prev_v = w.vertices[(ii - 1 + n_verts) % n_verts];
        Vec2 next_v = w.vertices[(ii + 1) % n_verts];
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

        f32 B = (EDGE_W * (a.dp(b) / b_len - a_len)) / b.dp(a_normal);

        inner_verts.push_back(
            curr_v.add(b.scl(B).add(b_normal.norm().scl(EDGE_W))));
      }

      for (u32 ii = 0; ii < n_verts; ++ii) {
        Vec2 curr_v = w.vertices[ii];
        Vec2 curr_v_in = inner_verts[ii]; // inner
        Vec2 next_v = w.vertices[(ii + 1) % n_verts];
        Vec2 next_v_in = inner_verts[(ii + 1) % n_verts]; // inner
        Vec2 outer_vec = next_v.sub(curr_v);
        f32 outer_vec_len = outer_vec.modulus(); // Side length

        // These 4 form a trapezium, which has 2 'caps' (triangles)

        // Find the start & end points of the outer line which are vertices
        // forming the cap
        Vec2 start_cap =
            curr_v.add(outer_vec.scl((curr_v_in.sub(curr_v)).dp(outer_vec) /
                                     (outer_vec_len * outer_vec_len)));
        Vec2 end_cap =
            next_v.sub(outer_vec.scl(-(next_v_in.sub(next_v)).dp(outer_vec) /
                                     (outer_vec_len * outer_vec_len)));

        // Draw the start and end 'cap' for the trapezium - since this method
        // draws quads just fudge it for now with a malformed quad, but should
        // really add a triangle method
        std::vector<Vertex> quads{
            Vertex(curr_v, &white, Vec2(t->uvs[0], t->uvs[1])),
            Vertex(start_cap, &white, Vec2(t->uvs[2], t->uvs[1])),
            Vertex(curr_v_in, &white, Vec2(t->uvs[2], t->uvs[3])),
            Vertex(curr_v_in, &white, Vec2(t->uvs[2], t->uvs[3])),

            Vertex(next_v, &white, Vec2(t->uvs[2], t->uvs[1])),
            Vertex(end_cap, &white, Vec2(t->uvs[0], t->uvs[1])),
            Vertex(next_v_in, &white, Vec2(t->uvs[0], t->uvs[3])),
            Vertex(next_v_in, &white, Vec2(t->uvs[0], t->uvs[3])),
        };

        // Now add the segment quads
        f32 middle_len = end_cap.sub(start_cap).modulus();
        Vec2 curr_seg_vec = start_cap; // Keep track of the pos of the current
        Vec2 curr_seg_vec_in = curr_v_in; // segment
        // The direction to progress in each loop iter:
        Vec2 prog_vec = outer_vec.norm().scl(SEG_LEN); 

        for (f32 ff = 0.0; ff < middle_len; ff += SEG_LEN) {
          Vec2 next_seg_vec = curr_seg_vec.add(prog_vec);
          Vec2 next_seg_vec_in = curr_seg_vec_in.add(prog_vec);
          Vertex quad[] = {
            Vertex(curr_seg_vec, &white, Vec2(t->uvs[0], t->uvs[1])),
            Vertex(next_seg_vec, &white, Vec2(t->uvs[2], t->uvs[1])),
            Vertex(next_seg_vec_in, &white, Vec2(t->uvs[2], t->uvs[3])),
            Vertex(curr_seg_vec_in, &white, Vec2(t->uvs[0], t->uvs[3])),
          };
          quads.insert(quads.end(), quad, quad + 4);
          curr_seg_vec = next_seg_vec;
          curr_seg_vec_in = next_seg_vec_in;
        }

        paint_controller->draw_quads(&(quads[0]), quads.size()/4, edge_tex);
      }
    }
  }
};
