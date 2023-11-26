#pragma once

#include "Window.h"
#include "../Camera/Camera2.h"
#include <glm/glm.hpp>
#include <vector>


namespace sim3D {

class FirstApp {
public:
  static constexpr int kWidth = 800;
  static constexpr int kHeight = 600;

  auto run() -> void;
  auto SetCameraMoving(bool status) -> void { m_camera_moving = status; }
  auto GetDeltaTime() -> float { return m_current_time - m_last_time; }
  /* auto CloseWindow() -> void { m_window.SetOpen(false); } */
private:
  sim3D::Window m_window{kWidth, kHeight, "Simulation"};
  sim3D::Camera m_camera{glm::vec3(0.0f, 0.0f, -3.0f)};
  bool m_camera_moving = false;
  float m_current_time;
  float m_last_time;
};

}
