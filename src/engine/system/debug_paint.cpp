#include "system.hpp"
#include "engine/input/input_state.hpp"
#include "engine/ecs.hpp"
#include "engine/renderer/paint_controller.hpp"
#include "engine/comp/game_entity.hpp"
#include "engine/color.hpp"

class SystemDebugPaint: public System {

  public:
    void handle_components(ECS* ecs, InputState* input_state, PaintController paint_controller) {
      Color red = Color(1.0, 0.0, 0.0, 1.0);
      for (u32 ii=0; ii < ecs->comp_game_entity.size(); ii++ ) {
        CompGameEntity entity = ecs->comp_game_entity[ii];
        paint_controller.fill_rect(-1.0 + entity.pos.x/100000, 0.0 + entity.pos.y/100000, 0.5, 0.5, &red);
      }
    }
};
