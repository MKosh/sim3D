#include "Window.h"
#include <GLFW/glfw3.h>
#include <iostream>

namespace sim3D {

Window::Window(int w, int h, std::string name)
  : m_width(w), m_height(h), m_name(name) {
  InitWindow();
}

Window::~Window() {
  glfwDestroyWindow(m_window);
  glfwTerminate();
}

auto Window::InitWindow() -> void {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  m_window = glfwCreateWindow(m_width, m_height, m_name.c_str(), nullptr, nullptr);
  if (m_window == nullptr) {
    std::cout << "Failed to create GLFW window\n";
    glfwTerminate();
  }

  glfwMakeContextCurrent(m_window);
}


} 
