#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include "InputHandler.h"
#include "../Camera/Camera.h"
#include "../App/App.h"

namespace sim3D {
InputHandler::InputHandler(sim3D::App* app)
  : m_app(app), m_camera(m_app->Camera()), m_window(m_app->Window()) {
  glfwSetFramebufferSizeCallback(m_window, FramebufferSizeCallback);
  glfwSetMouseButtonCallback(m_window, MouseButtonCallback);
  glfwSetKeyCallback(m_window, KeyCallback);
  glfwSetCursorEnterCallback(m_window, CursorEnterCallback);
  glfwSetScrollCallback(m_window, MouseScrollCallback);
}

auto InputHandler::ProcessKeyboard() -> void {
  float dt = m_app->GetDeltaTime();
  if (glfwGetKey(m_window, GLFW_KEY_W) == GLFW_PRESS) {
    m_camera.ProcessMovement(CameraMovement::kForward, dt);
  } else if (glfwGetKey(m_window, GLFW_KEY_W) == GLFW_RELEASE) {
    m_camera.ProcessMovement(CameraMovement::kForward, 0.0);
  }
  if (glfwGetKey(m_window, GLFW_KEY_S) == GLFW_PRESS) {
    m_camera.ProcessMovement(CameraMovement::kBackward, dt);
  } else if (glfwGetKey(m_window, GLFW_KEY_S) == GLFW_RELEASE) {
    m_camera.ProcessMovement(CameraMovement::kBackward, 0.0);
  }
  if (glfwGetKey(m_window, GLFW_KEY_A) == GLFW_PRESS) {
    m_camera.ProcessMovement(CameraMovement::kLeft, dt);
  } else if (glfwGetKey(m_window, GLFW_KEY_A) == GLFW_RELEASE) {
    m_camera.ProcessMovement(CameraMovement::kLeft, 0.0);
  }
  if (glfwGetKey(m_window, GLFW_KEY_D) == GLFW_PRESS) {
    m_camera.ProcessMovement(CameraMovement::kRight, dt);
  } else if (glfwGetKey(m_window, GLFW_KEY_D) == GLFW_RELEASE) {
    m_camera.ProcessMovement(CameraMovement::kRight, 0.0);
  }
  if (glfwGetKey(m_window, GLFW_KEY_UP) == GLFW_PRESS) {
    m_camera.ProcessMovement(CameraMovement::kUp, dt);
  } else if (glfwGetKey(m_window, GLFW_KEY_UP) == GLFW_RELEASE) {
    m_camera.ProcessMovement(CameraMovement::kUp, 0.0);
  }
  if (glfwGetKey(m_window, GLFW_KEY_DOWN) == GLFW_PRESS) {
    m_camera.ProcessMovement(CameraMovement::kDown, dt);
  } else if (glfwGetKey(m_window, GLFW_KEY_DOWN) == GLFW_RELEASE) {
    m_camera.ProcessMovement(CameraMovement::kDown, 0.0);
  }
}

auto InputHandler::ProcessMouse() -> void {
  if (glfwGetMouseButton(m_window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS
    && m_app->IsCameraMoving()) {
    double x_pos, y_pos;
    glfwGetCursorPos(m_window, &x_pos, &y_pos);
    m_camera.ProcessMouseMovement(x_pos, y_pos);
  } else if (glfwGetMouseButton(m_window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_RELEASE) {
  }
}

auto KeyCallback(GLFWwindow* window, int key, [[maybe_unused]] int scancode, int action, [[maybe_unused]] int mode) -> void {
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, GL_TRUE);
  }
  if (key == GLFW_KEY_R && action == GLFW_PRESS) {
    App::GetInstance()->Camera().ResetCamera();
  }
  if (key == GLFW_KEY_I && action == GLFW_PRESS) {

  }
}

auto MouseButtonCallback(GLFWwindow* window, int button, int action, int mods) -> void {
  if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS) {
    /* SetCameraMoving(true); */
    App::GetInstance()->SetCameraMoving(true);
    double x, y;
    glfwGetCursorPos(App::GetInstance()->Window(), &x, &y);
    sim3D::Vec2<float> pos;
    pos.x = (float)x;
    pos.y = (float)y;
    App::GetInstance()->Camera().SetMousePos(pos);
    /* glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL); */
  }
  if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE) {
    // SetCameraMoving(false);
    App::GetInstance()->SetCameraMoving(false);
    /* glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); */
  }
}

auto FramebufferSizeCallback(GLFWwindow* window, int width, int height) -> void {
  glViewport(0, 0, width, height);
}

auto CursorEnterCallback(GLFWwindow* window, int entered) -> void {
  if (!entered) {
    App::GetInstance()->SetCameraMoving(false);
  }
}

auto MouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset) -> void {
  App::GetInstance()->Camera().ProcessMouseScroll((float)yoffset);
}

/* auto Interactivecallback(GLFWwindow* window, int key, int scancode, int action, int mods) -> void { */
/*   if (key == GLFW_KEY_I && action == GLFW_PRESS) { */
/*     if (interactive == true) { */
/*       interactive = false; */
/*       glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL); */
/*     } else { */
/*       interactive = true; */
/*       glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); */
/*     } */
/*   } */
/* } */

}
