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
                   v2.subtract(v1).modulus_squared());
          //This means the collision does not fall within the line segment
          if (u <= 0 || u > 1) {
            continue;
          }

          Vec2 point_of_intersection =
              Vec2(v1.x + u * (v2.x - v1.x), v1.y + u * (v2.y - v1.y));

          Vec2 centre_to_wall_v = point_of_intersection.subtract(centre);
          f32 distance_to_wall = centre_to_wall_v.modulus_squared();
          if (std::pow((f64)radius, 2) > distance_to_wall) {
            // TODO: Handle collisions
            f64 actual_distance_to_wall = std::sqrt(distance_to_wall);

            f64 collision_depth = (f64)radius - actual_distance_to_wall;
            // https://www.opengl.org/discussion_boards/showthread.php/159717-Closest-point-on-a-Vector-to-a-point
            // In our case, P2 = centre, P1 = v1, and v = v2

            Vec2 radius_v =
                Vec2(radius * centre_to_wall_v.x / actual_distance_to_wall,
                     radius * centre_to_wall_v.y / actual_distance_to_wall);

            Vec2 to_push_back =
                Vec2(radius_v.x * collision_depth / (f64)radius,
                     radius_v.y * collision_depth / (f64)radius);

            e->pos.x -= to_push_back.x;
            e->pos.y -= to_push_back.y;
          }
        }
      }
    }
  }
};
