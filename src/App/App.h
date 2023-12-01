#pragma once

#include <glad/gl.h>
#include "Window.h"
#include "../Camera/Camera.h"
#include "../Input/InputHandler.h"
#include <glm/glm.hpp>
#include <vector>


namespace sim3D {

class App {
protected:
  App() {};
  static App* app;
public:
  static constexpr int kWidth = 800;
  static constexpr int kHeight = 600;

  auto run() -> void;
  auto SetCameraMoving(bool status) -> void { m_camera_moving = status; }
  auto GetDeltaTime() -> float { return m_current_time - m_last_time; }
  auto Shutdown() -> void;
  auto Window() -> GLFWwindow* { return m_window.GetWindow(); }
  auto IsCameraMoving() -> bool { return m_camera_moving; }
  auto operator=(const App&) = delete;
  static App* GetInstance();
private:

  sim3D::Window m_window{kWidth, kHeight, "Simulation"};
  sim3D::Camera m_camera{glm::vec3(0.0f, 0.0f, -3.0f)};
  sim3D::InputHandler m_input_handler{m_window.GetWindow()};
  bool m_camera_moving = false;
  float m_current_time;
  float m_last_time;
};

}
