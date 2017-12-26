#include "system.hpp"
#include "engine/ecs.hpp"


class SystemGravity: public System {

  public:
    void handle_components(ECS* ecs) {
      for (u32 ii=0; ii < ecs->comp_game_entity.size; ii++ ) {
        ecs->comp_game_entity[ii].y += 1;
      }
    }
}; 
