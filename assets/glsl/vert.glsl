#version 120

attribute vec3 pos;
attribute vec4 col;

varying vec4 v_col;

void main() {
  gl_Position = vec4(pos, 1.0);
  v_col = col;
}
