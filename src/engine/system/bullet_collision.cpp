#include "engine/comp/bullet.hpp"
#include "engine/ecs.hpp"
#include "engine/entity_id.hpp"
#include "engine/input/input_state.hpp"
#include "engine/system/update_system.hpp"
#include "globals.hpp"
#include <iostream>

class SystemBulletCollision : public UpdateSystem {
  public:
    void handle_components(Globals &globals) {
      auto ecs = globals.ecs;
      for(const auto& b : ecs->comp_bullet) {
        const auto& ge = *ecs->find_comp_game_entity_with_id(b.entity_id);

        for (u32 jj = 0; jj < ecs->comp_wall.size(); jj++) {

          CompWall &wall = ecs->comp_wall[jj];
          u32 vertices = wall.vertices.size();

          Vec2 centre = Vec2(ge.pos.x + 8.0, ge.pos.y + 8.0);
          f32 radius = 8.0;

          for (u32 kk = 0; kk < vertices; kk++) {
            // Start and end of wall respectively
            Vec2 v1 = wall.vertices[kk];
            Vec2 v2 = wall.vertices[(kk + 1) % vertices];

            // http://paulbourkge.net/geometry/pointlineplane/
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
              // if we're here, we've collided - delete the bullet
              ecs->queue_entity_death(b.entity_id);
              std::cout << "Deleting bullet: " << b.entity_id << std::endl;
              goto continue_outer_loop;
            }
          }
        }
continue_outer_loop:;
      }
    }
};
