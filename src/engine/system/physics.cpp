#include "engine/comp/game_entity.hpp"
#include "engine/ecs.hpp"
#include "engine/input/input_state.hpp"
#include "engine/renderer/paint_controller.hpp"
#include "system.hpp"

class SystemPhysics : public System {
public:
  void handle_components(ECS *ecs, InputState *input_state,
                         PaintController* paint_controller) {
    for (u32 ii = 0; ii < ecs->comp_game_entity.size(); ii++) {
      CompGameEntity *entity = &ecs->comp_game_entity[ii];
      entity->vel.x = (1 - entity->damping) * (entity->vel.x + entity->acc.x);
      entity->vel.y = (1 - entity->damping) * (entity->vel.y + entity->acc.y);

      entity->pos.x = entity->pos.x + entity->vel.x;
      entity->pos.y = entity->pos.y + entity->vel.y;

      entity->acc.x = 0.0f;
      entity->acc.y = 0.0f;
    }
  }
};
