#version 410 core

out vec4 FragColor;

uniform vec3 i_color;
uniform vec3 light_pos;
in vec3 normal;
in vec3 FragPos;

void main() {
  float ambient_strength = 0.5;
  vec3 ambient = ambient_strength * vec3(1.0, 1.0, 1.0);

  vec3 norm = normalize(normal);
  vec3 light_dir = normalize(light_pos - FragPos);

  float diff = max(dot(norm, light_dir), 0.0);
  vec3 diffuse = diff * vec3(1.0, 1.0, 1.0);


  vec3 result = (ambient + diffuse) * i_color;
  if (gl_FragCoord.x < 400) {
      FragColor = vec4(i_color, 1.0);
  } else {
      FragColor = vec4(result, 1.0);
  }
  // FragColor = vec4(result, 1.0);
  //FragColor = texture(texture_diffuse1, Tex_Coord);
}
