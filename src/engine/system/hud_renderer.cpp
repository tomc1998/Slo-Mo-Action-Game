#include "engine/camera.hpp"
#include "engine/color.hpp"
#include "engine/comp/game_entity.hpp"
#include "engine/ecs.hpp"
#include "engine/input/input_state.hpp"
#include "engine/renderer/paint_controller.hpp"
#include "engine/vec.hpp"
#include "globals.hpp"
#include "paint_system.hpp"

class SystemHudRenderer : public PaintSystem {
public:
  void handle_components(Globals &globals) {
    const auto &ecs = globals.ecs;
    const auto &paint_controller = globals.paint_controller;

    Color white = Color(1.0, 1.0, 1.0, 1.0);

    for (u32 ii = 0; ii < ecs->comp_hud_entity.size(); ii++) {
      CompHudEntity h = ecs->comp_hud_entity[ii];
      paint_controller->fill_rect(h.pos.x, h.pos.y, h.size.x, h.size.y, &white);
    }
  }
};
