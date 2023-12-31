#version 410 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 norm;
layout (location = 2) in vec2 tex;
layout (location = 3) in mat4 instance;

out vec3 normal;
out vec3 FragPos;
uniform mat4 pvm;
uniform vec3 i_color;
uniform vec3 light_pos;

void main() {
  gl_Position = pvm * instance * vec4(pos, 1.0);
  normal = norm;
  FragPos = vec3(pvm * vec4(pos, 1.0));
}
