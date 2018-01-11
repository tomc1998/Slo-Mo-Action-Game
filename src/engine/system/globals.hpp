#pragma once
#include "engine/resource_defs.hpp"

class InputState;
class PaintController;
class Camera;
class ECS;

/** A collection of standard texture handles, to be referenced across systems */
class StandardTextures {
public:
  TexHandle enemy_bullet;
};

/** A class which is passed into all the systems. Allows easy access to
 * 'uniforms' throughout all systems. */
class Globals {
public:
  ECS *ecs;
  InputState *input_state;
  /** Will be NULL if passed to an update system */
  PaintController *paint_controller;
  Camera *camera;
  StandardTextures *std_tex;
};
