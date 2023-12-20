#define GLFW_INCLUDE_NONE
#include <cstdlib>
#include <exception>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
// #include <iomanip>
// #include <sstream>
// #include <string>
// #include <cstdio>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_opengl3.h"

// #include <cstdint>
#include <iostream>

#include "Camera/Camera.h"
#include "Shader/Shader.h"
#include "Input/InputHandler.h"
#include "App/App.h"
#include "Model/Model.h"
#include "Model/Mesh.h"
#include "Model/Box.h"


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
