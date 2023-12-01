#pragma once

#include <GLFW/glfw3.h>

#include "../Camera/Camera.h"

namespace sim3D {

auto FramebufferSizeCallback(GLFWwindow* window, int width, int height) -> void;
auto KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode) -> void;
auto MouseButtonCallback(GLFWwindow* window, int button, int action, int mods) -> void;

class InputHandler {
public:

  InputHandler(GLFWwindow* window);

private:
  GLFWwindow* m_window;

};

}
