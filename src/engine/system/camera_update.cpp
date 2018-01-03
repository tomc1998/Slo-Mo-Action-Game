#include "engine/camera.hpp"
#include "engine/comp/game_entity.hpp"
#include "engine/ecs.hpp"
#include "engine/input/input_state.hpp"
#include "update_system.hpp"

class SystemCameraUpdate : public UpdateSystem {
public:
  void handle_components(ECS *ecs, InputState *input_state, Camera *camera) {
    for (u32 ii = 0; ii < ecs->comp_game_entity.size(); ii++) {
      for (u32 jj = 0; jj < ecs->comp_player_controlled.size(); jj++) {
        if (ecs->comp_player_controlled[jj].entity_id !=
            ecs->comp_game_entity[ii].entity_id) {
          continue;
        }

        camera->pos.x += 0.01*((ecs->comp_game_entity[ii].pos.x + 8.0) - camera->pos.x);
        camera->pos.y += 0.01*((ecs->comp_game_entity[ii].pos.y + 8.0) - camera->pos.y);

      }
    }
  }
};
