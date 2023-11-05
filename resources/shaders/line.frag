#version 410 core

uniform vec3 line_color;
out vec4 FragColor;

void main() {
  FragColor = vec4(line_color, 1.0);
}
