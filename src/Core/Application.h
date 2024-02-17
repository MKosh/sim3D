#pragma once

#include <glad/gl.h>
#include "Window.h"
#include "Renderer/Camera.h"
#include "Simulation/Simulation.h"
#include <glm/glm.hpp>
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

namespace sim3D {

auto FramebufferSizeCallback(GLFWwindow* window, int width, int height) -> void;
auto KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode) -> void;
auto MouseButtonCallback(GLFWwindow* window, int button, int action, int mods) -> void;
auto MouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset) -> void;
auto CursorEnterCallback(GLFWwindow* window, int enter) -> void;


class App {
protected:
  App() {
    InitGLAD();
    SetupCallbackfunctions();
    InitImGui();

  };
  static App* app;
public:
  static constexpr int kWidth = 800;
  static constexpr int kHeight = 600;

  //////////////////////////////////////////////////////////////////////////////
  /// Core application functions
  auto run() -> void;
  auto Shutdown() -> void;
  auto GetDeltaTime() -> float { return m_dt; }
  auto InitGLAD() -> void;
  auto operator=(const App&) = delete;
  auto SetDeltaTime(sim3D::Simulation& sim) -> void;
  auto SetupCallbackfunctions() -> void;
  static App* GetInstance();

  //////////////////////////////////////////////////////////////////////////////
  /// Window functions
  auto Window() -> GLFWwindow* { return m_window.GetWindow(); }
  auto GetWindow() -> sim3D::Window& {return m_window; }

  //////////////////////////////////////////////////////////////////////////////
  /// Camera functions
  auto Camera() -> sim3D::Camera& { return m_camera; }
  auto IsCameraMoving() -> bool { return m_camera_moving; }
  auto SetCameraMoving(bool status) -> void { m_camera_moving = status; }

  //////////////////////////////////////////////////////////////////////////////
  /// Input handler functions
  auto ProcessKeyboard() -> void;
  auto ProcessMouse() -> void;

  //////////////////////////////////////////////////////////////////////////////
  /// UI functions
  auto InitImGui() -> void;
private:

  sim3D::Window m_window{kWidth, kHeight, "Simulation"};
  sim3D::Camera m_camera{glm::vec3(0.0f, 0.0f, -3.0f)};
  bool m_camera_moving = false;
  float m_current_time;
  float m_last_time = 0.0f;
  float m_dt;
  int m_gl_flags;
};

}
