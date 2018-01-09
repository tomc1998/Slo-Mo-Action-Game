#include "engine/comp/animation.hpp"
#include "engine/camera.hpp"
#include "engine/ecs.hpp"
#include "engine/input/input_state.hpp"
#include "update_system.hpp"
#include "globals.hpp"

class SystemAnimationUpdate : public UpdateSystem {
public:
  void handle_components(Globals &globals) {
    const auto& ecs = globals.ecs;
    for (u32 ii = 0; ii < ecs->comp_animation.size(); ii++) {
      ecs->comp_animation[ii].updates++;
      if (ecs->comp_animation[ii].updates >= ecs->comp_animation[ii].length) {
        ecs->comp_animation[ii].updates = 0;
      }
    }
  }
};
