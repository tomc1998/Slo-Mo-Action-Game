#include "system.hpp"
#include "engine/input/input_state.hpp"
#include "engine/ecs.hpp"

class SystemPhysics: public System {
  public:
    void handle_components(ECS* ecs, InputState* input_state) {
      for (u32 ii=0; ii < ecs->comp_game_entity.size(); ii++) {
        ecs->comp_game_entity[ii].vel.x  = ecs->comp_game_entity[ii].vel.x + ecs->comp_game_entity[ii].acc.x;
        ecs->comp_game_entity[ii].vel.y  = ecs->comp_game_entity[ii].vel.y + ecs->comp_game_entity[ii].acc.y;

        ecs->comp_game_entity[ii].pos.x  = ecs->comp_game_entity[ii].pos.x + ecs->comp_game_entity[ii].vel.x;
        ecs->comp_game_entity[ii].pos.y  = ecs->comp_game_entity[ii].pos.y + ecs->comp_game_entity[ii].vel.y;

        ecs->comp_game_entity[ii].acc.x = 0.0f;
        ecs->comp_game_entity[ii].acc.y = 0.0f;
      }
    }
};
