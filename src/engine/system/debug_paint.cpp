#include "engine/color.hpp"
#include "engine/comp/game_entity.hpp"
#include "engine/comp/sprite.hpp"
#include "engine/ecs.hpp"
#include "engine/input/input_state.hpp"
#include "engine/renderer/paint_controller.hpp"
#include "engine/vec.hpp"
#include "paint_system.hpp"
#include <iostream>
#define _USE_MATH_DEFINES
#include <cmath>

class SystemDebugPaint : public PaintSystem {

public:
  void handle_components(ECS *ecs, InputState *input_state,
                         PaintController *paint_controller) {
    Color white = Color(1.0, 1.0, 1.0, 1.0);
    Color red = Color(1.0, 0.0, 0.0, 1.0);
    for (u32 ii = 0; ii < ecs->comp_game_entity.size(); ii++) {
      CompGameEntity entity = ecs->comp_game_entity[ii];
      for (u32 jj = 0; jj < ecs->comp_animations.size(); jj++) {
        if (entity.entity_id != ecs->comp_animations[jj].entity_id) {
          continue;
        }
        CompAnimations *as = &ecs->comp_animations[jj];

        assert(as->animation_to_play >= -1 &&
               as->animation_to_play < as->animations.size());
        if (as->animation_to_play == -1) {
          paint_controller->draw_image(as->th, entity.pos.x, entity.pos.y, 16.0,
                                       16.0, 0.0, &white);
          break;
        }
        Animation *a = &as->animations[animation_to_play];
        paint_controller->draw_image(
            a->th, entity.pos.x + a->get_interpolated_value(as->updates, 0),
            entity.pos.y + a->get_interpolated_value(as->updates, 1),
            16.0 * a->get_interpolated_value(as->updates, 2),
            16.0 * a->get_inter_polated_value(as->updates, 2),
            0.0 + a->get_interpolated_value(as->updates, 3), &white);
        break;
      }
    }
    for (u32 ii = 0; ii < ecs->comp_wall.size(); ii++) {
      for (u32 jj = 0; jj < ecs->comp_wall[ii].vertices.size(); jj++) {
        Vec2 vertex = ecs->comp_wall[ii].vertices[jj];
        paint_controller->fill_rect(vertex.x, vertex.y, 1.0, 1.0, &red);
      }
    }
  }
};
