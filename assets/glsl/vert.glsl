#version 120

uniform mat4 proj_mat;

attribute vec2 uv;
attribute vec3 pos;
attribute vec4 col;

varying vec4 v_col;
varying vec2 v_uv;

void main() {
  gl_Position = proj_mat * vec4(pos, 1.0);
  v_col = col;
  v_uv = uv;
}
