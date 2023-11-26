#pragma once

/* #include <GLFW/glfw3.h> */

#include "../Camera/Camera.h"
#include "../App/App.h"

auto ProcessEvents(App& scene) -> void;
auto ProcessKeyboard(App& scene) -> void;
auto ProcessMouse(App& scene) -> void;

/* auto FramebufferSizeCallback(GLFWwindow* window, int width, int height); */
