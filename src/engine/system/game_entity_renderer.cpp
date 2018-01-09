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
    for (u32 ii = 0; ii < ecs->comp_game_entity.size(); ii++) {
      CompGameEntity entity = ecs->comp_game_entity[ii];
      for (u32 jj = 0; jj < ecs->comp_animation.size(); jj++) {
        if (entity.entity_id != ecs->comp_animation[jj].entity_id) {
          continue;
        }
        CompAnimation a = ecs->comp_animation[jj];

        paint_controller->draw_animation(a.anim, a.updates, entity.pos.x,
                                         entity.pos.y, 16.0, 16.0,
                                         entity.rot, &white);
        break;
      }
      for (u32 jj = 0; jj < ecs->comp_sprite.size(); jj++) {
        if (entity.entity_id != ecs->comp_sprite[jj].entity_id) {
          continue;
        }
        CompSprite s = ecs->comp_sprite[jj];
        paint_controller->draw_image(s.tex, entity.pos.x, entity.pos.y, 16.0f,
                                     16.0f, entity.rot, &white);
        break;
      }
    }
  }
};
