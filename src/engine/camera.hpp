#pragma once
#include "vec.hpp"

/** Camera class that generates a projection matrix based on x and y, width in
 * units, and an aspect ratio */
class Camera {
private:
  /* x and y of the CENTRE of what the camera is focusing on */
  Vec2 pos;

  Vec2 target_pos;

  /** width in units, not pixels */
  f32 w;

  f32 target_w;

  /* Aspect ratio of width/height (e.g.16/9) */
  f32 aspect_ratio;

  
public:
  /* fills 16 f32s based on the current x, y, width, and aspect ratio */
  void gen_ortho_proj_mat(f32 *dest);
  
  void update();

  /**
   *
   * @param[in] pos The initial position of the camera
   * @param[in] w The initial width of the camera's view
   * @param[in] aspect_ratio The initial aspect ratio of the camera
   * (width/height)
   *
   */
  Camera(Vec2 pos, f32 w, f32 aspect_ratio);
};
