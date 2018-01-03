#include "camera.hpp"

void Camera::gen_ortho_proj_mat(f32 *dest) {

  f32 l = this->x - this->w/2;
  f32 r = this->x + this->w/2;

  f32 h = this->w/this->aspect_ratio;
  f32 t = this->y - h/2;
  f32 b = this->y + h/2;

  f32 n = -1.0;
  f32 f = 1.0;

  dest[0] = 2.0 / (r - l);
  dest[1] = 0.0;
  dest[2] = 0.0;
  dest[3] = -(r + l) / (r - l);

  dest[4] = 0.0;
  dest[5] = 2.0 / (t - b);
  dest[6] = 0.0;
  dest[7] = -(t + b) / (t - b);

  dest[8] = 0.0;
  dest[9] = 0.0;
  dest[10] = -2.0 / (f - n);
  dest[11] = -(f + n) / (f - n);

  dest[12] = 0.0;
  dest[13] = 0.0;
  dest[14] = 0.0;
  dest[15] = 1.0;

}

Camera::Camera(f32 x, f32 y, f32 w, f32 aspect_ratio) {
  this->x = x;
  this->y = y;
  this->w = w;
  this->aspect_ratio = aspect_ratio;
}
