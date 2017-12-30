#include "engine/comp/animations.hpp"
#include "engine/ecs.hpp"
#include "engine/input/input_state.hpp"
#include "update_system.hpp"

class SystemAnimationUpdate : public UpdateSystem {
public:
  void handle_components(ECS *ecs, InputState *input_state) {
    for (u32 ii = 0; ii < ecs->comp_animations.size(); ii++) {
      ecs->comp_animations[ii].updates++;
    }
  }
};
