#include <cstdlib>
#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iomanip>
#include <sstream>
#include <string>
#include <cstdio>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_opengl3.h"

#include <cstdint>
#include <iostream>

#include "Camera/Camera.h"
#include "Shader/Shader.h"
#include "Input/InputHandler.h"
#include "App/App.h"
#include "Model/Model.h"
#include "Model/Mesh.h"
#include "Model/Box.h"


[[maybe_unused]]const uint32_t kScreenWidth  = 800;
[[maybe_unused]]const uint32_t kScreenHeight = 600;

sim3D::App* sim3D::App::app = nullptr;

int main () {

  auto app = sim3D::App::GetInstance();

  int version = gladLoadGL(glfwGetProcAddress);
  if (!version) {
    std::cout << "Failed to initialize GLAD\n";
    return -1;
  }

  /* sim3D::Camera camera(glm::vec3(0.0f, 0.0f, -3.0f)); */

  stbi_set_flip_vertically_on_load(true);

  app->run();

  /* Shader ball_shader{"resources/shaders/ball.vert", "resources/shaders/ball.frag"}; */
  /* Shader line_shader{"resources/shaders/line.vert", "resources/shaders/line.frag"}; */
  /**/
  /**/
  /* Model ball_model("resources/models/sphere/sphere3.obj"); */
  /* Box box{}; */
  /**/
  /* glad_glEnable(GL_DEPTH_TEST); */
  /* float current_time = (float)glfwGetTime(); */
  /* float last_time = 0.0f; */
  /* float dt = current_time - last_time; */
  /* [[maybe_unused]]float frames = 1.0f/dt; */
  /* char fps[10]; */

  /* while (!glfwWindowShouldClose(app->Window())) { */

    /* float dt = clock.restart().asSeconds(); */

    /* glfwPollEvents(); */

    /* last_time = current_time; */
    /* current_time = (float)glfwGetTime(); */
    /* dt = current_time - last_time; */
    /* frames = 1.0f/dt; */
    /* std::cout << "FPS: " << frames << '\n'; */

    /* fps << frames; */
    /* button->setText(std::to_string(1.0f/dt)); */
    /* fps.str(""); */

    /* sprintf(fps, "%6.2f", 1.0f/dt); */
    /* button->setText(fps); */
    /* app.SetDeltaTime(dt); */

    /* ProcessEvents(app); */
    /* ProcessKeyboard(app); */
    /* ProcessMouse(app); */

    /* glad_glClearColor(0.2, 0.5, 0.8, 1.0); */
    /* glad_glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); */

    /* glm::mat4 model = glm::mat4(1.0f); */
    /* glm::mat4 projection = glm::perspective(glm::radians(camera.GetZoom()), static_cast<float>(kScreenWidth)/kScreenHeight, 0.05f, 100.0f); */
    /* glm::mat4 view = camera.GetViewMatrix(); */
    /* glm::mat4 pvm = projection * view * model; */

    /* ball_shader.Use(); */

    /* model = glm::mat4(1.0f); */
    /* model = glm::translate(model, glm::vec3(0.0f, 0.0f, 1.0f)); */
    /* model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0)); */
    

    /* pvm = projection * view * model; */
    /* ball_shader.SetMat4("pvm", pvm); */
    /* ball_shader.SetVec3f("i_color", glm::vec3(0.75f, 0.3f, 0.3f)); */
    /* float time = clock2.getElapsedTime().asSeconds(); */
    /* ball_shader.SetVec3f("light_pos", glm::vec3(cos(time), 2.0f, sin(time))); */
  /*   ball_shader.SetVec3f("light_pos", glm::vec3(0.0f, 2.0f, 1.0f)); */
  /**/
  /*   glad_glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); */
  /*   ball_model.Draw(ball_shader); */
  /**/
  /*   // Draw line */
  /*   line_shader.Use(); */
  /*   model = glm::mat4(1.0f); */
  /*   model = glm::translate(model, glm::vec3(0.0f, 0.0f, 1.0f)); */
  /*   model = glm::scale(model, glm::vec3(1.0, 1.0, 1.0)); */
  /*   pvm = projection * view * model; */
  /*   line_shader.SetVec3f("line_color", glm::vec3(1.0, 1.0, 1.0)); */
  /*   line_shader.SetMat4("pvm", pvm); */
  /*   box.Draw(); */
  /**/
  /**/
  /*   glfwSwapBuffers(app->Window()); */
  /* } */

  glfwTerminate();
  gladLoaderUnloadGL();
  return 0;
}
