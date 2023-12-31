#version 410 core

layout (location = 0) in vec3 a_pos;
layout (location = 1) in vec3 a_norm;
layout (location = 2) in vec2 a_tex_coord;

out vec2 tex_coord;

uniform mat4 pvm;
uniform vec3 i_color;

void main() {
  tex_coord = a_tex_coord;
  gl_Position = pvm * vec4(a_pos, 1.0);
}
