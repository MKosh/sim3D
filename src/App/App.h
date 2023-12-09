#pragma once

#include <glad/gl.h>
#include "Window.h"
#include "../Camera/Camera.h"
#include "../Input/InputHandler.h"
#include <glm/glm.hpp>
#include <vector>

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

namespace sim3D {


class App {
protected:
  App() {
    InitGLAD();
  };
  static App* app;
public:
  static constexpr int kWidth = 800;
  static constexpr int kHeight = 600;

  auto run() -> void;
  auto SetCameraMoving(bool status) -> void { m_camera_moving = status; }
  auto GetDeltaTime() -> float { return m_dt; }
  auto Shutdown() -> void;
  auto Window() -> GLFWwindow* { return m_window.GetWindow(); }
  auto GetWindow() -> sim3D::Window& {return m_window; }
  auto Camera() -> sim3D::Camera& { return m_camera; }
  auto IsCameraMoving() -> bool { return m_camera_moving; }
  auto InitGLAD() -> void;
  auto SetDeltaTime() -> void;
  auto operator=(const App&) = delete;
  static App* GetInstance();
private:

  sim3D::Window m_window{kWidth, kHeight, "Simulation"};
  sim3D::Camera m_camera{glm::vec3(0.0f, 0.0f, -3.0f)};
  bool m_camera_moving = false;
  float m_current_time;
  float m_last_time = 0.0f;
  float m_dt;
};

}
