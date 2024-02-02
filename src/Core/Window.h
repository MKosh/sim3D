#pragma once

#include <GLFW/glfw3.h>
#include <string>

namespace sim3D {

class Window {
public:
  Window(int w, int h, std::string name);
  ~Window();
  auto IsOpen() -> bool { return m_window_is_open; }
  auto SetOpen(bool status) -> void { m_window_is_open = status; }
  auto Close() -> void {}
  auto ShouldClose() -> void { glfwSetWindowShouldClose(m_window,m_window_is_open); }
  auto GetWindow() -> GLFWwindow* { return m_window; }
private:
  GLFWwindow* m_window;
  const int m_width;
  const int m_height;
  std::string m_name;
  bool m_window_is_open;

  auto InitWindow() -> void;
};

}
