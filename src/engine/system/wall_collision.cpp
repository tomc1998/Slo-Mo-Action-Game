#include "engine/comp/wall.hpp"
#include "engine/vec.hpp"
#include <iostream>
#include "update_system.hpp"
#include "globals.hpp"
#include "engine/ecs.hpp"
#include <cmath>

class SystemWallCollision : public UpdateSystem {
public:
  void handle_components(Globals &globals) {
    const auto& ecs = globals.ecs;
    for (auto &ge : ecs->comp_game_entity) {
      auto p_circ_coll = ecs->find_comp_circle_collider_with_id(ge.entity_id);
      if (!p_circ_coll || !p_circ_coll->collides_with_walls) {
        continue;
      }
      auto& circ_coll = *p_circ_coll;

      for (auto &wall : ecs->comp_wall) {
        u32 vertices = wall.vertices.size();

        for (u32 kk = 0; kk < vertices; kk++) {
          // Start and end of wall respectively
          Vec2 v1 = wall.vertices[kk];
          Vec2 v2 = wall.vertices[(kk + 1) % vertices];

          // http://paulbourke.net/geometry/pointlineplane/
          f64 u = (((ge.pos.x - v1.x) * (v2.x - v1.x) +
                    (ge.pos.y - v1.y) * (v2.y - v1.y)) /
                   (v2-v1).len2());

          // This means the collision does not fall within the line segment
          if (u <= 0 || u > 1) {
            continue;
          }

          Vec2 point_of_intersection = (v2-v1)*u + v1;

          Vec2 centre_to_wall_v = point_of_intersection - ge.pos;
          f32 distance_to_wall = centre_to_wall_v.len2();
          if (std::pow((f64)circ_coll.rad, 2) > distance_to_wall) {
            f64 actual_distance_to_wall = std::sqrt(distance_to_wall);

            f64 collision_depth = (f64)circ_coll.rad - actual_distance_to_wall;

            // This is just normalising the vector and then scaling it. I didn#t
            // use the norm() method beause I had already calculated the len
            // so there was no point in wasting time doing that
            Vec2 rad_v =
                centre_to_wall_v * (circ_coll.rad / actual_distance_to_wall);

            Vec2 to_push_back = rad_v * (collision_depth / circ_coll.rad);

            ge.pos -= to_push_back;
          }
        }
      }
    }
  }
};
