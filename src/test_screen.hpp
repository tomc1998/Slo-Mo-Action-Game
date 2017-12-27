#include "engine/screen.hpp"

class TestScreen: public Screen {
  public:
    void init(ECS* ecs);
    ~TestScreen();
};
