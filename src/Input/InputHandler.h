#pragma once

#include <GLFW/glfw3.h>

/* #inlcude "../App/App.h" */
#include "../Camera/Camera.h"
#include "../App/Window.h"

namespace sim3D {

class App;

auto FramebufferSizeCallback(GLFWwindow* window, int width, int height) -> void;
auto KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode) -> void;
auto MouseButtonCallback(GLFWwindow* window, int button, int action, int mods) -> void;
auto MouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset) -> void;
auto CursorEnterCallback(GLFWwindow* window, int enter) -> void;

class InputHandler {
public:

  InputHandler(sim3D::App* app);
  auto ProcessKeyboard() -> void;
  auto ProcessMouse() -> void;

private:
  sim3D::App* m_app;
  sim3D::Camera& m_camera;
  GLFWwindow* m_window;
};

}
