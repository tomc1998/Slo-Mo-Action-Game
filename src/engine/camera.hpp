#pragma once
#include "vec.hpp"

/** Camera class that generates a projection matrix based on x and y, width in
 * units, and an aspect ratio */
class Camera {
private:
  /** x and y of the CENTRE of what the camera is focusing on */
  Vec2 pos;

  /** The position the camera will move towards */
  Vec2 target_pos;

  /** width in units, not pixels */
  f32 w;

  /** The view width the camera will zoom towards */
  f32 target_w;

  /** Aspect ratio of width/height (e.g.16/9) */
  f32 aspect_ratio;

  /** Default width of the camera */
  f32 default_w;

public:
  /** fills 16 f32s based on the current x, y, width, and aspect ratio */
  void gen_ortho_proj_mat(f32 *dest);

  /** Moves the camera a percentage of the distance to the target pos */
  void update_pos();

  /** Changes the width of the camera a percentage of the distance to the target
   * width */
  void update_width();

  Vec2 get_top_left();

  /**
   *
   * @param[in] pos The initial position of the camera
   * @param[in] w The initial width of the camera's view
   * @param[in] aspect_ratio The initial aspect ratio of the camera
   * (width/height)
   *
   */
  Camera(Vec2 pos, f32 w, f32 aspect_ratio);

  /** Sets the target pos */
  void set_target_pos(Vec2 pos);

  /** Sets the target width */
  void set_target_width(f32 w);

  /** Converts screen coordinates to world coordinates */
  Vec2 screen_to_world(Vec2 pos);

  f32 get_width();

};
