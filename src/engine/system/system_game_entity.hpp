#pragma once
#include "system.hpp"

class ECS;

class SystemGravity: public System {

  public:
    void handle_components(ECS* ecs) {
      for (component=0; component < ecs->comp_game_entity.size; component ++ ) {
        ecs->comp_game_entity[component].y += 1;
      }
    }
}; 
