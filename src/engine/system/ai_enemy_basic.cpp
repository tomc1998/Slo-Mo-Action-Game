#include "engine/camera.hpp"
#include "engine/comp/ai_enemy_basic.hpp"
#include "engine/comp/game_entity.hpp"
#include "engine/ecs.hpp"
#include "engine/entity_id.hpp"
#include "engine/input/input_state.hpp"
#include "engine/system/update_system.hpp"
#include "engine/system/globals.hpp"
#include <iostream>

class SystemAIEnemyBasic : public UpdateSystem {
private:
  /** Shoot a bullet at a given target from the given position with a given
   * speed. */
  void shoot_bullet(ECS* ecs, TexHandle tex, Vec2 pos, Vec2 target, f32 speed) {
    EntityId e_id = ecs->gen_entity_id();
    CompGameEntity ge(e_id, pos, 1.0f, 0.0f, false);
    CompSprite sprite(e_id, tex);
    CompBullet bullet(e_id, 4);
    ge.vel = (target - pos).nor() * speed;  
    ecs->add_comp_game_entity(ge);
    ecs->add_comp_sprite(sprite);
    ecs->add_comp_bullet(bullet);
  }

  /**
   * Given a list of walls, a list of enemy positions, and a player position,
   * return a list of enemies which can currently see the player.
   *
   * This is just based on points, so if the player is technically visible
   * but the player's centre point is not, the enemy will not be reported as
   * being able to see the player.
   *
   * The returned list of entity IDs will be order preserved.
   */
  std::vector<EntityId> is_vision_obstructed(const CompWall *walls,
                                             const u32 count_walls,
                                             const CompGameEntity *enemies,
                                             const u32 count_enemies,
                                             const Vec2 player_pos) {
    std::vector<EntityId> entities_with_vision;
    entities_with_vision.reserve(count_enemies);
    for (u32 ii = 0; ii < count_enemies; ++ii) {
      const auto enemy_pos = enemies[ii].pos;
      bool can_see = true;
      // Now loop over the walls until we hit a wall segment which collides
      // with the line from the centre of the player to the centre of the
      // enemy
      for (u32 jj = 0; jj < count_walls; ++jj) {
        const auto &wall = walls[jj];
        for (u32 kk = 0; kk < wall.vertices.size(); ++kk) {
          // Find the vertices making up this wall segment, then check a
          // collision
          Vec2 w0 = wall.vertices[kk];
          Vec2 w1 = wall.vertices[(kk + 1) % wall.vertices.size()];

          // http://paulbourke.net/geometry/pointlineplane/
          // We want to find ua and ub, which is like a lerp value between 0-1
          // which is the point of the intersection. If both are between 0 and
          // 1 then there is a collision.
          //
          // If the lines are parallel, there will be a division by 0, so we
          // need to check for that first:
          f32 denom = (w1.y - w0.y) * (enemy_pos.x - player_pos.x) -
                      (w1.x - w0.x) * (enemy_pos.y - player_pos.y);
          if (denom != 0.0f) {
            f32 ua = ((w1.x - w0.x) * (player_pos.y - w0.y) -
                     (w1.y - w0.y) * (player_pos.x - w0.x)) /
                    denom;
            f32 ub = ((enemy_pos.x - player_pos.x) * (player_pos.y - w0.y) -
                     (enemy_pos.y - player_pos.y) * (player_pos.x - w0.x)) /
                    denom;
            if (ua >= 0.0 && ua <= 1.0 && ub >= 0.0 && ub <= 1.0) {
              // This collides, so the enemy doesn't have vision - just continue
              // to the next enemy [C++ no named loops killme]
              can_see = false;
              goto break_wall_loop;
            }
          }
        }
      }
    break_wall_loop:
      if (can_see) {
        entities_with_vision.push_back(enemies[ii].entity_id);
      }
    }
    return entities_with_vision;
  }

public:
  void handle_components(Globals &globals) {
    const auto& ecs = globals.ecs;
    // Make sure there's a player controlled entities on screen! If there
    // isn't, just return, no need to process any AI stuff
    if (ecs->comp_player_controlled.size() == 0) {
      return;
    }

    // First, join the enemies with their game entity components.
    // Indices of these vectors are matched.
    std::vector<CompGameEntity> enemy_ge_list;
    std::vector<CompAIEnemyBasic> enemy_ai_list;
    enemy_ge_list.reserve(ecs->comp_ai_enemy_basic.size());
    enemy_ai_list.reserve(ecs->comp_ai_enemy_basic.size());
    for (u32 jj = 0; jj < ecs->comp_ai_enemy_basic.size(); jj++) {
      // TODO: Once component lists are sorted we can binary search here
      for (u32 ii = 0; ii < ecs->comp_game_entity.size(); ii++) {
        CompAIEnemyBasic ai = ecs->comp_ai_enemy_basic[jj];
        CompGameEntity ge = ecs->comp_game_entity[ii];
        if (ai.entity_id != ge.entity_id) {
          continue;
        }
        enemy_ge_list.push_back(ge);
        enemy_ai_list.push_back(ai);
      }
    }

    const auto &player_pc = ecs->comp_player_controlled[0];
    CompGameEntity *p_player_ge;
    // Now, find the player game entity component
    for (u32 ii = 0; ii < ecs->comp_game_entity.size(); ii++) {
      if (ecs->comp_game_entity[ii].entity_id == player_pc.entity_id) {
        p_player_ge = &ecs->comp_game_entity[ii];
        break;
      }
    }
    const auto &player_ge = *p_player_ge;

    // Now get a list of the enemies which have vision
    std::vector<EntityId> enemies_with_vision = is_vision_obstructed(
        &ecs->comp_wall[0], ecs->comp_wall.size(), &enemy_ge_list[0],
        enemy_ge_list.size(), player_ge.pos);

    // Now loop over and apply enemy behaviour. We can't use the joined lists
    // from earlier - these are copies of the components, so mutations won't
    // apply.
    for (u32 jj = 0; jj < ecs->comp_ai_enemy_basic.size(); jj++) {
      // TODO: Once component lists are sorted we can binary search here
      for (u32 ii = 0; ii < ecs->comp_game_entity.size(); ii++) {
        auto &ai = ecs->comp_ai_enemy_basic[jj];
        auto &ge = ecs->comp_game_entity[ii];
        if (ai.entity_id != ge.entity_id) {
          continue;
        }

        // Check if this enemy has vision...
        // TODO: Once we have sorted component lists we can optimise this by
        // binary searching
        bool has_vision = false;
        for (const auto &e : enemies_with_vision) {
          if (e == ai.entity_id) {
            has_vision = true;
            break;
          }
        }

        if (ai.get_state() == ai.STATE_NORMAL) {
          if (has_vision) {
            std::cout << "Transitioning AI to state 'waiting on reaction'"
                      << std::endl;
            ai.set_state(ai.STATE_WAITING_ON_REACTION);
          }
        } else if (ai.get_state() == ai.STATE_WAITING_ON_REACTION) {
          if (!has_vision) { // Player disappeared, go back to normal
            std::cout << "Lost vision of player." << std::endl;
            ai.set_state(ai.STATE_NORMAL);
          } else if (ai.state_change_timer >= ai.reaction_delay) {
            ai.set_state(ai.SPOTTED_PLAYER);
            std::cout << "Transitioning AI to state 'spotted player'"
                      << std::endl;
          }
        } else if (ai.get_state() == ai.SPOTTED_PLAYER) {
          if (!has_vision) { // Player disappeared, go back to normal...
            // here we'd put in some kind of chasing AI
            std::cout << "Lost vision of player." << std::endl;
            ai.set_state(ai.STATE_NORMAL);
          } else {
            // Shoot
            if (ai.reload_timer > ai.RELOAD_TIME) {
              shoot_bullet(ecs, globals.std_tex->enemy_bullet, ge.pos, player_ge.pos, 20.0f);
              ai.reload_timer = 0;
            }
            else {
              ai.reload_timer ++;
            }
          }
        }
        ai.state_change_timer++;
      }
    }
  }
};
