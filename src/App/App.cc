#include "App.h"
#include <array>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shader/Shader.h"
#include "Model/Model.h"
#include "Model/Mesh.h"
#include "Model/Box.h"

#include <GLFW/glfw3.h>

#include <iostream>
#include <stdexcept>
#include <vector>


namespace sim3D {

auto App::GetInstance() -> App* {
  if (app == nullptr) {
    app = new App();
  }
  return app;
}

auto App::InitGLAD() -> void {
  int version = gladLoadGL(glfwGetProcAddress);
  if (!version) {
    std::cerr << "Failed to initialize GLAD\n";
    throw std::runtime_error("ERROR::App Failed to initialize GLAD");
  }
  return;
}

auto App::SetDeltaTime() -> void {
  m_current_time = (float)glfwGetTime();
  m_dt = m_current_time - m_last_time;
  m_last_time = m_current_time;
}

auto App::run() -> void {

  ImGui::CreateContext();

  InputHandler input{app};

  ImGui_ImplGlfw_InitForOpenGL(app->Window(), true);
  ImGui_ImplOpenGL3_Init();

  // glGetError();
  glad_glEnable(GL_DEPTH_TEST);
  Shader ball_shader{"resources/shaders/ball.vert", "resources/shaders/ball.frag"};
  Shader line_shader{"resources/shaders/line.vert", "resources/shaders/line.frag"};

  Model ball_model("resources/models/sphere/sphere3.obj");
  Box box{};
  float box_width = 1.0f;
  float box_height = 1.0f;
  float box_depth = 1.0f;
  float ball_radius = 0.5f;

  while (!glfwWindowShouldClose(m_window.GetWindow())) {

    SetDeltaTime();
 
    glfwPollEvents();
    input.ProcessKeyboard();
    input.ProcessMouse();

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();


    float fps = 1.0/GetDeltaTime();

    glad_glClearColor(0.2, 0.5, 0.8, 1.0);
    glad_glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 projection = glm::perspective(glm::radians(m_camera.GetZoom()), static_cast<float>(kWidth)/kHeight, 0.05f, 100.0f);
    glm::mat4 view = m_camera.GetViewMatrix();
    glm::mat4 pvm = projection * view * model;

    ball_shader.Use();

    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::scale(model, glm::vec3(ball_radius, ball_radius, ball_radius));

    pvm = projection * view * model;
    ball_shader.SetMat4("pvm", pvm);
    ball_shader.SetVec3f("i_color", glm::vec3(0.75f, 0.3f, 0.3f));
    ball_shader.SetVec3f("light_pos", glm::vec3(0.0f, 10.0f, -1.0f));

    // glad_glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    ball_model.Draw(ball_shader);

    // Draw line */
    line_shader.Use();
    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::scale(model, glm::vec3(box_width, box_height, box_depth));
    pvm = projection * view * model;
    line_shader.SetVec3f("line_color", glm::vec3(1.0, 1.0, 1.0));
    line_shader.SetMat4("pvm", pvm);
    box.Draw();

    ImGui::Text("FPS: %f", fps);
    ImGui::Begin("Box Controls");
    ImGui::SliderFloat("x", &box_width, 0.01f, 10.0f);
    ImGui::SliderFloat("y", &box_height, 0.01f, 10.0f);
    ImGui::SliderFloat("z", &box_depth, 0.01f, 10.0f);
    ImGui::End();
    ImGui::Begin("Ball Controls");
    ImGui::SliderFloat("radius", &ball_radius, 0.01f, 1.0f);
    ImGui::End();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    glfwSwapBuffers(m_window.GetWindow());
  }

  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();

  glfwTerminate();
  gladLoaderUnloadGL();
}

/* auto App::Shutdown() -> void { */
/*   m_window.ShouldClose(true); */
/* } */

}
