#include "InputHandler.h"
#include "../Camera/Camera.h"
/* #include "../App/App.h" */
#include <GL/gl.h>
#include <GLFW/glfw3.h>

/* auto ProcessEvents(App& app) -> void { */
/*   sf::Window& window = app.GetWindow(); */
/*   sf::Event event; */
/*   std::cout << "processing events\n"; */
/*   while (window.pollEvent(event)) { */
/*     if (event.type == sf::Event::KeyPressed) { */
/*       if (event.key.scancode == sf::Keyboard::Scan::Escape) { */
/*         app.SetOpen(false); */
/*       } */
/*       if (event.key.scancode == sf::Keyboard::Scan::R) { */
/*         app.GetCamera().ResetCamera(); */
/*       } */
/*       if (event.key.scancode == sf::Keyboard::Scan::Space) { */
/*         app.TogglePhysics(); */
/*       } */
/*     } */
/*     if (event.type == sf::Event::Closed) { */
/*         app.SetOpen(false); */
/*     } */
/*     if (event.type == sf::Event::Resized) { */
/*       glad_glViewport(0, 0, event.size.width, event.size.height); */
/*     } */
/*     if (event.type == sf::Event::MouseWheelScrolled) { */
/*       app.GetCamera().ProcessMouseScroll(event.mouseWheelScroll.delta); */
/*     } */
/*     if (event.type == sf::Event::MouseButtonPressed) { */
/*       if (event.mouseButton.button == sf::Mouse::Button::Right) { */
/*         app.GetCamera().SetMousePos(sf::Mouse::getPosition(window)); */
/*         app.SetCameraMoving(true); */
/*       } */
/*     } */
/*     if (event.type == sf::Event::MouseButtonReleased) { */
/*       if (event.mouseButton.button == sf::Mouse::Button::Right) { */
/*         app.SetCameraMoving(false); */
/*       } */
/*     } */
/*   } */
/* } */

/* auto ProcessKeyboard(App& app) -> void { */
/*   if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::W)) { */
/*     app.GetCamera().ProcessMovement(CameraMovement::kForward, app.GetDeltaTime()); */
/*   } */
/*   if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::S)) { */
/*     app.GetCamera().ProcessMovement(CameraMovement::kBackward, app.GetDeltaTime()); */
/*   } */
/*   if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::A)) { */
/*     app.GetCamera().ProcessMovement(CameraMovement::kLeft, app.GetDeltaTime()); */
/*   } */
/*   if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::D)) { */
/*     app.GetCamera().ProcessMovement(CameraMovement::kRight, app.GetDeltaTime()); */
/*   } */
/*   if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Up)) { */
/*     app.GetCamera().ProcessMovement(CameraMovement::kUp, app.GetDeltaTime()); */
/*   } */
/*   if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Down)) { */
/*     app.GetCamera().ProcessMovement(CameraMovement::kDown, app.GetDeltaTime()); */
/*   } */
/* } */
/**/
/* auto ProcessMouse(App& app) -> void { */
/*   if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right) && app.IsCameraMoving() == true) { */
/*     app.GetCamera().ProcessMouseMovement(sf::Mouse::getPosition(app.GetWindow())); */
/*   } */
/* } */

namespace sim3D {
InputHandler::InputHandler(GLFWwindow* window)
  : m_window(window) {
  glfwSetFramebufferSizeCallback(m_window, FramebufferSizeCallback);
  glfwSetMouseButtonCallback(m_window, MouseButtonCallback);
  glfwSetKeyCallback(m_window, KeyCallback);

}

auto KeyCallback(GLFWwindow* window, int key, [[maybe_unused]] int scancode, int action, [[maybe_unused]] int mode) -> void {
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, GL_TRUE);
  }
}

auto MouseButtonCallback(GLFWwindow* window, int button, int action, int mods) -> void {
  if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS) {
    /* SetCameraMoving(true); */
  }
  if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE) {
    // SetCameraMoving(false);
  }
}

auto FramebufferSizeCallback(GLFWwindow* window, int width, int height) -> void {
  glViewport(0, 0, width, height);
}

}
