#version 410 core

layout (location = 0) in vec3 pos;

uniform vec3 line_color;
uniform mat4 pvm;

void main() {
  gl_Position = pvm * vec4(pos, 1.0);
}
