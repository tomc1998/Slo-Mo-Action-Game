#pragma once
#include "engine/camera.hpp"
#include "engine/ecs.hpp"
#include "engine/input/input_state.hpp"
#include "engine/renderer/paint_controller.hpp"
#include "engine/texture.hpp"

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
