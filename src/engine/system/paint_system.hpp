#pragma once
#include "engine/ecs.hpp"
#include "engine/input/input_state.hpp"
#include "engine/renderer/paint_controller.hpp"
#include "engine/camera.hpp"
#include "globals.hpp"

/** Paint system base class with a virtual function to handle components of the
 * ECS */
class PaintSystem {
public:
  virtual void handle_components(Globals &globals) = 0;
  virtual ~PaintSystem(){};
};
