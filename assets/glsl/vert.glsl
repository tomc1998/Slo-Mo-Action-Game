#version 120

uniform mat4 proj_mat;

attribute vec3 pos;
attribute vec4 col;

varying vec4 v_col;

void main() {
  gl_Position = proj_mat * vec4(pos, 1.0);
  v_col = col;
}
