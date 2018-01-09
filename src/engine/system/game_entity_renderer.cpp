#include "engine/anim_frame.hpp"
#include "engine/camera.hpp"
#include "engine/color.hpp"
#include "engine/comp/animation.hpp"
#include "engine/comp/game_entity.hpp"
#include "engine/ecs.hpp"
#include "engine/input/input_state.hpp"
#include "engine/renderer/paint_controller.hpp"
#include "engine/vec.hpp"
#include "globals.hpp"
#include "paint_system.hpp"
#include <iostream>
#define _USE_MATH_DEFINES
#include <cmath>

class SystemGameEntityRenderer : public PaintSystem {

public:
  void handle_components(Globals &globals) {
    const auto &ecs = globals.ecs;
    const auto &paint_controller = globals.paint_controller;
    Color white = Color(1.0, 1.0, 1.0, 1.0);

    for (u32 ii = 0; ii < ecs->comp_animation.size(); ii++) {
      CompAnimation &a = ecs->comp_animation[ii];
      CompGameEntity &entity = ecs->find_comp_game_entity_with_id(a.entity_id);
      paint_controller->draw_animation(a.anim, a.updates, entity.pos.x,
                                       entity.pos.y, 16.0, 16.0, entity.rot,
                                       &white);
    }
    for (u32 ii = 0; ii < ecs->comp_sprite.size(); ii++) {
      CompSprite &s = ecs->comp_sprite[ii];
      CompGameEntity &entity = ecs->find_comp_game_entity_with_id(s.entity_id);
      paint_controller->draw_image(s.tex, entity.pos.x, entity.pos.y, 16.0f,
                                   16.0f, entity.rot, &white);
    }
  }
}
}
;
