#version 120

uniform sampler2D tex;

varying vec4 v_col;
varying vec2 v_uv;

void main() {
  gl_FragColor = v_col * texture2D(tex, v_uv);
}
