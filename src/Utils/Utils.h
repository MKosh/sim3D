#pragma once

// #include <glad/gl.h>
#include "gl.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

namespace sim3D::Utils {

////////////////////////////////////////////////////////////////////////////////
/// Debug callback for OpenGL
void GLAPIENTRY DebugCallback(GLenum source, GLenum type, GLuint id, GLenum severity,
                              GLsizei length, const GLchar* message, const void* userParam);

////////////////////////////////////////////////////////////////////////////////
/// Nothing function that prints nothing.
void nothing();


////////////////////////////////////////////////////////////////////////////////
/// Render UI
auto RenderUI(ImGuiIO& io) -> void;
}
