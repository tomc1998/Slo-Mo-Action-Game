#pragma once
#include "engine/ecs.hpp"
#include "engine/input/input_state.hpp"
#include "engine/renderer/paint_controller.hpp"

/** Paint system base class with a virtual function to handle components of the
 * ECS */
class PaintSystem {
public:
  virtual void handle_components(ECS *ecs, InputState *input_state,
                                 PaintController paint_controller) = 0;
};
