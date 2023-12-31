# version 410 core

layout (location = 0) in vec3 a_pos;
layout (location = 1) in vec3 a_color;

out vec3 color;

//uniform mat4 transform;
uniform mat4 pvm;


void main() {
  gl_Position = pvm * vec4(a_pos, 1.0); //transform * vec4(a_pos, 1.0);
  color = a_color;
}
