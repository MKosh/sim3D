#pragma once

#include <SFML/Window.hpp>

#include "../Camera/Camera.h"

class App {
public:
  App(sf::Window& window, Camera& camera) : m_window(window), m_camera(camera) {}
  auto GetWindow() -> sf::Window& { return m_window; }
  auto GetCamera() -> Camera&     { return m_camera; }
  auto IsOpen() -> bool { return m_window_open; }
  auto SetOpen(bool open) -> void { m_window_open = open; }
  auto GetDeltaTime() -> float { return m_delta_time; }
  auto SetDeltaTime(float dt) -> void { m_delta_time = dt; }
  auto IsCameraMoving() -> bool { return m_camera_moving; }
  auto SetCameraMoving(bool move) -> void { m_camera_moving = move; }
  auto TogglePhysics() -> void;

private:
  sf::Window& m_window;
  Camera& m_camera;
  bool m_window_open = true;
  bool m_camera_moving = false;
  bool m_physics_active = false;
  float m_delta_time;
};
