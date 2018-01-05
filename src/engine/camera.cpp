#include "camera.hpp"
#include "vec.hpp"

void Camera::gen_ortho_proj_mat(f32 *dest) {

  f32 l = this->pos.x - this->w/2;
  f32 r = this->pos.x + this->w/2;

  f32 h = this->w/this->aspect_ratio;
  f32 t = this->pos.y - h/2;
  f32 b = this->pos.y + h/2;

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

void Camera::update_pos() {
  if (this->pos != this->target_pos) {
    this->pos += (this->target_pos - this->pos) * 0.01f;
  }
}

void Camera::update_width() {
  if (this->w != this->target_w) {
    this->w += (this->target_w - this->w) * 0.01f;
  }
}

Camera::Camera(Vec2 pos, f32 w, f32 aspect_ratio) {
  this->pos = pos;
  this->w = w;
  this->aspect_ratio = aspect_ratio;

  this->target_pos = pos;
  this->target_w = w;
}

void Camera::set_target_pos(Vec2 pos) {
  this->target_pos = pos;
}

void Camera::set_target_width(f32 w) {
  this->target_w = w;
}

Vec2 Camera::get_top_left() {
  f32 h = this->w/this->aspect_ratio;
  return Vec2(this->pos.x - this->w/2, this->pos.y - h/2);
}
