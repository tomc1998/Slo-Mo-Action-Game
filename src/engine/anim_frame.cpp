#include "anim_frame.hpp"
#include "texture.hpp"

AnimFrame::AnimFrame() {
  this->th = -1;
  this->posx = 0.0;
  this->posy = 0.0;
  this->scale = 1.0;
  this->rot = 0.0;
}

AnimFrame::AnimFrame(TexHandle th) {
  this->th = th;
  this->posx = 0.0;
  this->posy = 0.0;
  this->scale = 1.0;
  this->rot = 0.0;
}
