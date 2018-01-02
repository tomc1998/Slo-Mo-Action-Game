#include "engine/comp/animation.hpp"
#include "engine/ecs.hpp"
#include "engine/input/input_state.hpp"
#include "update_system.hpp"

class SystemAnimationUpdate : public UpdateSystem {
public:
  void handle_components(ECS *ecs, InputState *input_state) {
    for (u32 ii = 0; ii < ecs->comp_animation.size(); ii++) {
      ecs->comp_animation[ii].updates++;
      if (ecs->comp_animation[ii].updates >= ecs->comp_animation[ii].length) {
        ecs->comp_animation[ii].updates = 0;
      }
    }
  }
};
