#define GLFW_INCLUDE_NONE
#include "Application.h"
#include <cstdlib>
#include <iostream>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Renderer/Shader.h"
#include "Renderer/Model.h"
#include "Renderer/Box.h"
#include "Renderer/VertexBuffer.h"

#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_glfw.h"
#include "imgui/backends/imgui_impl_opengl3.h"

#include <GLFW/glfw3.h>


namespace sim3D {

void GLAPIENTRY DebugCallback(GLenum source, GLenum type, GLuint id, GLenum severity,
                              GLsizei length, const GLchar* message, const void* userParam) {
  std::cout << "OpenGL ERROR: " << "\n\t" << message << std::endl;
}

auto App::GetInstance() -> App* {
  if (app == nullptr) {
    app = new App();
  }
  return app;
}

auto App::InitGLAD() -> void {
  // int version = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
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

  InitGLAD();
  ImGui::CreateContext();

  InputHandler input{app};

  //////////////////////////////////////////////////////////////////////////////
  // Dear ImGui
  ImGui_ImplGlfw_InitForOpenGL(app->Window(), true);
  ImGui_ImplOpenGL3_Init();

  ImGuiIO& io = ImGui::GetIO();
  io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;


  glad_glEnable(GL_DEPTH_TEST);
  glad_glEnable(GL_CULL_FACE);
  glad_glEnable(GL_POLYGON_SMOOTH);
  glad_glEnable(GL_DEBUG_OUTPUT);
  glad_glDebugMessageCallback(sim3D::DebugCallback, 0);

  std::cout << "OpenGL version: " << glad_glGetString(GL_VERSION) << '\n';
  Shader ball_shader{"data/shaders/ball.vert", "data/shaders/ball.frag"};
  Shader line_shader{"data/shaders/line.vert", "data/shaders/line.frag"};

  // Model ball_model("data/models/sphere/ico_2.obj");
  Model ball_model("data/models/sphere/5seg_5ring.obj");
  Box box{};
  float box_width = 1.0f;
  float box_height = 1.0f;
  float box_depth = 1.0f;
  float ball_radius = 0.5f;

  std::vector<glm::mat4> ball_models;
  std::srand(0);
  std::size_t instances = 1;
  for (std::size_t i = 0; i < instances; i++) {
    ball_models.emplace_back(glm::mat4(1.0f));
    float r1 = ((float) rand() / (RAND_MAX)) * 8 - 4;
    float r2 = ((float) rand() / (RAND_MAX)) * 8 - 4;
    float r3 = ((float) rand() / (RAND_MAX)) * 8 - 4;
    ball_models[i] = glm::translate(ball_models[i], glm::vec3(r1, r2, r3));
    ball_models[i] = glm::translate(ball_models[i], glm::vec3(0.0, 0.0, 10.0));
    ball_models[i] = glm::scale(ball_models[i], glm::vec3(0.1, 0.1, 0.1));
  }
  ball_model.SetInstances(instances);

  VertexBuffer positions;
  positions.SetData(ball_models, sizeof(glm::mat4));

  VertexBufferLayout instance_layout;
  instance_layout.Push<float>(4);
  instance_layout.Push<float>(4);
  instance_layout.Push<float>(4);
  instance_layout.Push<float>(4);
  ball_model.AddProperty(positions, instance_layout, 3);
  ball_model.SetPropertyDivisor(3, 1);
  ball_model.SetPropertyDivisor(4, 1);
  ball_model.SetPropertyDivisor(5, 1);
  ball_model.SetPropertyDivisor(6, 1);

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
    // glad_glClearColor(0.0, 0.0, 0.0, 1.0);
    glad_glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 projection = glm::perspective(glm::radians(m_camera.GetZoom()), static_cast<float>(kWidth)/kHeight, 0.05f, 100.0f);
    glm::mat4 view = m_camera.GetViewMatrix();
    glm::mat4 pvm = projection * view * model;

    ball_shader.Use();

    model = glm::mat4(1.0f);
    // model = glm::translate(model, glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::scale(model, glm::vec3(ball_radius, ball_radius, ball_radius));
    pvm = projection * view;
    ball_shader.SetMat4("pvm", pvm);
    ball_shader.SetVec3f("i_color", glm::vec3(0.75f, 0.3f, 0.3f));
    ball_shader.SetVec3f("light_pos", glm::vec3(0.0f, 10.0f, -1.0f));

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

    // Dear ImGui code. Will refactor later
    //

    ImGui::BeginMainMenuBar();
    if (ImGui::BeginMenu("File")) {
      ImGui::MenuItem("New");
      ImGui::MenuItem("junk");
      ImGui::EndMenu();
    }
    ImGui::EndMainMenuBar();

    ImGui::Begin("Stats");
    ImGui::Text("FPS: %.1f", io.Framerate);
    ImGui::Text("Frame time %.3f ms", 1000.0f / io.Framerate);
    ImGui::End();

    ImGui::Begin("Controls");
    if (ImGui::CollapsingHeader("Box Controls", ImGuiTreeNodeFlags_None)) {
      ImGui::SliderFloat("x", &box_width, 0.01f, 10.0f);
      ImGui::SliderFloat("y", &box_height, 0.01f, 10.0f);
      ImGui::SliderFloat("z", &box_depth, 0.01f, 10.0f);
    }
    if (ImGui::CollapsingHeader("Particle Controls", ImGuiTreeNodeFlags_None)) {
      ImGui::SliderFloat("radius", &ball_radius, 0.01f, 1.0f);
    }
    ImGui::End();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    glfwSwapBuffers(m_window.GetWindow());
  }

  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();

  glfwTerminate();
}

/* auto App::Shutdown() -> void { */
/*   m_window.ShouldClose(true); */
/* } */

}
