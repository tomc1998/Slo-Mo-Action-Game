#include "engine/comp/wall.hpp"
#include "engine/ecs.hpp"
#include "engine/input/input_state.hpp"
#include "engine/vec.hpp"
#include "update_system.hpp"
#include <cmath>
#include <iostream>

class SystemWallCollision : public UpdateSystem {
public:
  void handle_components(ECS *ecs, InputState *input_state) {
    for (u32 ii = 0; ii < ecs->comp_game_entity.size(); ii++) {
      if (!ecs->comp_game_entity[ii].collides_with_walls) {
        continue;
      }

      CompGameEntity *e = &ecs->comp_game_entity[ii];
      for (u32 jj = 0; jj < ecs->comp_wall.size(); jj++) {
        // TODO: Change +8s to be +width/2 and +height/2

        CompWall *wall = &ecs->comp_wall[jj];
        u32 vertices = wall->vertices.size();

        Vec2 centre = Vec2(e->pos.x + 8.0, e->pos.y + 8.0);
        f32 radius = 8.0;

        for (u32 kk = 0; kk < vertices; kk++) {
          // Start and end of wall respectively
          Vec2 v1 = wall->vertices[kk];
          Vec2 v2 = wall->vertices[(kk + 1) % vertices];

          // http://paulbourke.net/geometry/pointlineplane/

          f64 u = (((centre.x - v1.x) * (v2.x - v1.x) +
                    (centre.y - v1.y) * (v2.y - v1.y)) /
                   (v2-v1).len2());

          // This means the collision does not fall within the line segment
          if (u <= 0 || u > 1) {
            continue;
          }

          Vec2 point_of_intersection = (v2-v1)*u + v1;

          Vec2 centre_to_wall_v = point_of_intersection - centre;
          f32 distance_to_wall = centre_to_wall_v.len2();
          if (std::pow((f64)radius, 2) > distance_to_wall) {
            f64 actual_distance_to_wall = std::sqrt(distance_to_wall);

            f64 collision_depth = (f64)radius - actual_distance_to_wall;

            // This is just normalising the vector and then scaling it. I didn#t
            // use the norm() method beause I had already calculated the len
            // so there was no point in wasting time doing that
            Vec2 radius_v =
                centre_to_wall_v * (radius / actual_distance_to_wall);

            Vec2 to_push_back = radius_v * (collision_depth / radius);

            e->pos -= to_push_back;
          }
        }
      }
    }
  }
};
