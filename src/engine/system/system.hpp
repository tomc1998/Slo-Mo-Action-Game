#pragma once

// Forward declaration
class ECS;

/** System base class with a virtual function to handle components of the ECS */
class System {
  public:
    virtual void handle_components(ECS* ecs);
};
