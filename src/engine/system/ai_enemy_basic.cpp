#include "engine/camera.hpp"
#include "engine/comp/ai_enemy_basic.hpp"
#include "engine/ecs.hpp"
#include "engine/input/input_state.hpp"
#include "engine/system/update_system.hpp"
#include <iostream>

class SystemAIEnemyBasic : public UpdateSystem {
public:
  void handle_components(ECS *ecs, InputState *input_state, Camera *camera) {
    for (u32 jj = 0; jj < ecs->comp_ai_enemy_basic.size(); jj++) {
      for (u32 ii = 0; ii < ecs->comp_game_entity.size(); ii++) {
        CompAIEnemyBasic &ai = ecs->comp_ai_enemy_basic[jj];
        CompGameEntity &ge = ecs->comp_game_entity[ii];
        if (ai.entity_id != ge.entity_id) {
          continue;
        }
        if (ai.get_state() == ai.STATE_NORMAL) {
          // check if this ai has spotted the player yet... ??

          std::cout << "Transitioning AI to state 'waiting on reaction'"
                    << std::endl;
          ai.set_state(ai.STATE_WAITING_ON_REACTION);
        } else if (ai.get_state() == ai.STATE_WAITING_ON_REACTION) {
          if (ai.state_change_timer >= ai.reaction_delay) {
            ai.set_state(ai.SPOTTED_PLAYER);
            std::cout << "Transitioning AI to state 'spotted player'"
                      << std::endl;
          }
        } else if (ai.get_state() == ai.SPOTTED_PLAYER) {
          // Start shooting
          std::cout << "Shooting" << std::endl;
        }
        ai.state_change_timer++;
      }
    }
  }
};
