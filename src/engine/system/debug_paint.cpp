#include "engine/color.hpp"
#include "engine/comp/game_entity.hpp"
#include "engine/ecs.hpp"
#include "engine/vec.hpp"
#include "engine/input/input_state.hpp"
#include "engine/renderer/paint_controller.hpp"
#include "paint_system.hpp"
#include <iostream>

class SystemDebugPaint : public PaintSystem {

public:
  void handle_components(ECS *ecs, InputState *input_state,
                         PaintController* paint_controller) {
    Color red = Color(1.0, 0.0, 0.0, 1.0);
    for (u32 ii = 0; ii < ecs->comp_game_entity.size(); ii++) {
      CompGameEntity entity = ecs->comp_game_entity[ii];
      paint_controller->fill_rect(entity.pos.x, entity.pos.y, 16.0, 16.0, &red);
    }
    for (u32 ii = 0; ii < ecs->comp_wall.size(); ii++) {
      for (u32 jj = 0; jj < ecs->comp_wall[ii].vertices.size(); jj++) {
        Vec2 vertex = ecs->comp_wall[ii].vertices[jj];
        paint_controller->fill_rect(vertex.x, vertex.y, 1.0, 1.0, &red);

      }
    }
  }
};
