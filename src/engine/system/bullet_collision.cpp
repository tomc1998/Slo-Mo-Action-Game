#include "engine/comp/bullet.hpp"
#include "engine/ecs.hpp"
#include "engine/entity_id.hpp"
#include "engine/input/input_state.hpp"
#include "engine/system/update_system.hpp"
#include "globals.hpp"

class SystemBulletCollision : public UpdateSystem {
public:
  void handle_components(Globals &globals) {
    // TODO: Implement bullet collisions
  }
};
