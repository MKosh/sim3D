#define GLFW_INCLUDE_NONE
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image/stb_image.h"

// #include <cstdint>
#include <iostream>

#include "Core/Application.h"


sim3D::App* sim3D::App::app = nullptr;

int main () {

  auto app = sim3D::App::GetInstance();

  stbi_set_flip_vertically_on_load(true);

  try {
    app->run();
  } catch (std::exception& e) {
    std::cout << "App failed to run with: " << e.what();
  } 

  return 0;
}
