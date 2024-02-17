#include "Simulation/Simulation.h"
// #define GLFW_INCLUDE_NONE
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
// #include "UI.h"
#include "Utils/Utils.h"
#include "imgui.h"

#include <GLFW/glfw3.h>


namespace sim3D {

/// Create singleton
auto App::GetInstance() -> App* {
  if (app == nullptr) {
    app = new App();
  }
  return app;
}

/// Initialize GLAD, throw an error if there's an issue
auto App::InitGLAD() -> void {
  int version = gladLoadGL(glfwGetProcAddress);
  if (!version) {
    std::cerr << "Failed to initialize GLAD\n";
    throw std::runtime_error("ERROR::App Failed to initialize GLAD");
  }
  glad_glEnable(GL_DEPTH_TEST);
  glad_glEnable(GL_CULL_FACE);
  glad_glEnable(GL_POLYGON_SMOOTH);
  std::cout << "OpenGL version: " << glad_glGetString(GL_VERSION) << '\n';
  return;
}

/// Set up the glfw callback functions, as well as OpenGL debug callback
auto App::SetupCallbackfunctions() -> void {
  glfwSetFramebufferSizeCallback(Window(), FramebufferSizeCallback);
  glfwSetMouseButtonCallback(Window(), MouseButtonCallback);
  glfwSetKeyCallback(Window(), KeyCallback);
  glfwSetCursorEnterCallback(Window(), CursorEnterCallback);
  glfwSetScrollCallback(Window(), MouseScrollCallback);
  
  #ifdef MYDEBUG
    glad_glEnable(GL_DEBUG_OUTPUT);
    glad_glDebugMessageCallback(sim3D::Utils::DebugCallback, 0);
    glGetIntegerv(GL_CONTEXT_FLAGS, &m_gl_flags);
    if (m_gl_flags & GL_CONTEXT_FLAG_DEBUG_BIT) {
      std::cout << "Debugging is active!\n";
    }
  #endif
}

auto App::InitImGui() -> void {

  ImGui::CreateContext();

  ImGui_ImplGlfw_InitForOpenGL(Window(), true);
  ImGui_ImplOpenGL3_Init();

  ImGuiIO& io = ImGui::GetIO();
  io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

}

///
/// Function definition
///
auto App::SetDeltaTime(sim3D::Simulation& sim) -> void { // TODO: Should take a simulation reference and set the delta time for that as well
  m_current_time = (float)glfwGetTime();
  m_dt = m_current_time - m_last_time;
  m_last_time = m_current_time;
  sim.SetDeltaTime(m_dt);
}

auto App::run() -> void {

  ImGuiIO& io = ImGui::GetIO();
  sim3D::Simulation sim;

  Shader ball_shader{"data/shaders/ball.vert", "data/shaders/ball.frag"};
  Shader line_shader{"data/shaders/line.vert", "data/shaders/line.frag"};

  Model ball_model("data/models/sphere/ico_3.obj");
  // Box box{};
  float box_width = 1.0f;
  float box_height = 1.0f;
  float box_depth = 1.0f;
  float ball_radius = 0.5f;

  std::vector<glm::mat4> ball_models;
  std::srand(0);
  std::size_t instances = 100;
  for (std::size_t i = 0; i < instances; i++) {
    ball_models.emplace_back(glm::mat4(1.0f));
    float r1 = ((float) rand() / (RAND_MAX)) * 8 - 4;
    float r2 = ((float) rand() / (RAND_MAX)) * 8 - 4;
    float r3 = ((float) rand() / (RAND_MAX)) * 8 - 4;
    ball_models[i] = glm::translate(ball_models[i], glm::vec3(r1, r2, r3));
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

  while (!glfwWindowShouldClose(Window())) {
    SetDeltaTime(sim);
 
    glfwPollEvents();
    ProcessKeyboard();
    ProcessMouse();

    glad_glClearColor(0.2, 0.5, 0.8, 1.0);
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
    sim.Draw(pvm);

    Utils::RenderUI(io);
    glfwSwapBuffers(Window());
  }

  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();

  glfwTerminate();
}

auto App::ProcessKeyboard() -> void {
  float dt = GetDeltaTime();
  if (glfwGetKey(Window(), GLFW_KEY_W) == GLFW_PRESS) {
    m_camera.ProcessMovement(CameraMovement::kForward, dt);
  } else if (glfwGetKey(Window(), GLFW_KEY_W) == GLFW_RELEASE) {
    m_camera.ProcessMovement(CameraMovement::kForward, 0.0);
  }
  if (glfwGetKey(Window(), GLFW_KEY_S) == GLFW_PRESS) {
    m_camera.ProcessMovement(CameraMovement::kBackward, dt);
  } else if (glfwGetKey(Window(), GLFW_KEY_S) == GLFW_RELEASE) {
    m_camera.ProcessMovement(CameraMovement::kBackward, 0.0);
  }
  if (glfwGetKey(Window(), GLFW_KEY_A) == GLFW_PRESS) {
    m_camera.ProcessMovement(CameraMovement::kLeft, dt);
  } else if (glfwGetKey(Window(), GLFW_KEY_A) == GLFW_RELEASE) {
    m_camera.ProcessMovement(CameraMovement::kLeft, 0.0);
  }
  if (glfwGetKey(Window(), GLFW_KEY_D) == GLFW_PRESS) {
    m_camera.ProcessMovement(CameraMovement::kRight, dt);
  } else if (glfwGetKey(Window(), GLFW_KEY_D) == GLFW_RELEASE) {
    m_camera.ProcessMovement(CameraMovement::kRight, 0.0);
  }
  if (glfwGetKey(Window(), GLFW_KEY_UP) == GLFW_PRESS) {
    m_camera.ProcessMovement(CameraMovement::kUp, dt);
  } else if (glfwGetKey(Window(), GLFW_KEY_UP) == GLFW_RELEASE) {
    m_camera.ProcessMovement(CameraMovement::kUp, 0.0);
  }
  if (glfwGetKey(Window(), GLFW_KEY_DOWN) == GLFW_PRESS) {
    m_camera.ProcessMovement(CameraMovement::kDown, dt);
  } else if (glfwGetKey(Window(), GLFW_KEY_DOWN) == GLFW_RELEASE) {
    m_camera.ProcessMovement(CameraMovement::kDown, 0.0);
  }
}

auto App::ProcessMouse() -> void {
  if (glfwGetMouseButton(Window(), GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS
    && IsCameraMoving()) {
    double x_pos, y_pos;
    glfwGetCursorPos(Window(), &x_pos, &y_pos);
    m_camera.ProcessMouseMovement(x_pos, y_pos);
  } else if (glfwGetMouseButton(Window(), GLFW_MOUSE_BUTTON_RIGHT) == GLFW_RELEASE) {
  }
}
/* auto App::Shutdown() -> void { */
/*   m_window.ShouldClose(true); */
/* } */

}
