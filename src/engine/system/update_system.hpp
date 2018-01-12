#pragma once

class Globals;

/** Paint system base class with a virtual function to handle components of the
 * ECS */
class UpdateSystem {
public:
  virtual void handle_components(Globals &globals) = 0;
  virtual ~UpdateSystem(){};
};
