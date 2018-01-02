#include "anim_frame.hpp"
#include "texture.hpp"

AnimFrame::AnimFrame() {
  this->tex = -1;
  this->posx = 0.0;
  this->posy = 0.0;
  this->scale = 1.0;
  this->rot = 0.0;
}

AnimFrame::AnimFrame(TexHandle th) {
  this->tex = tex;
  this->posx = 0.0;
  this->posy = 0.0;
  this->scale = 1.0;
  this->rot = 0.0;
}
