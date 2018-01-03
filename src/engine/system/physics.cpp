#include "engine/comp/game_entity.hpp"
#include "engine/ecs.hpp"
#include "engine/input/input_state.hpp"
#include "engine/camera.hpp"
#include "engine/renderer/paint_controller.hpp"
#include "update_system.hpp"
#include <iostream>

class SystemPhysics : public UpdateSystem {
  static constexpr f32 T = 0.016;

public:
  void handle_components(ECS *ecs, InputState *input_state, Camera *camera) {
    for (u32 ii = 0; ii < ecs->comp_game_entity.size(); ii++) {
      CompGameEntity *e = &ecs->comp_game_entity[ii];

      // s = ut + (1/2)at^2
      e->pos.x += e->vel.x * T + 0.5 * e->acc.x * T * T;
      e->pos.y += e->vel.y * T + 0.5 * e->acc.y * T * T;

      // v = u + at
      e->vel.x = (1.0 - e->damping) * (e->vel.x + e->acc.x * T);
      e->vel.y = (1.0 - e->damping) * (e->vel.y + e->acc.y * T);

      e->acc.x = 0.0f;
      e->acc.y = 0.0f;
    }
  }
};
