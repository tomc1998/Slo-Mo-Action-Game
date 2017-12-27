#pragma once
#include "engine/input/input_state.hpp"
#include "engine/ecs.hpp"

/** System base class with a virtual function to handle components of the ECS */
class System {
  public:
    virtual void handle_components(ECS* ecs, InputState* input_state) = 0;
};
