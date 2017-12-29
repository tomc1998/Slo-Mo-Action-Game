#include "engine/screen.hpp"

class TestScreen : public Screen {
public:
  void init(ECS *ecs, ResourceManager *res_manager);
  ~TestScreen();
};
