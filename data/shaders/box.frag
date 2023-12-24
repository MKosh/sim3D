#version 410 core

out vec4 FragColor;

in vec2 tex_coord;

uniform vec3 i_color;

//uniform sampler2D texture_diffuse1;

void main() {
  FragColor = vec4(i_color, 1.0);
  //FragColor = texture(texture_diffuse1, tex_coord);
  //FragColor = vec4(1.0, 0.5, 0.2, 1.0);
}
