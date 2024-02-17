#include "Utils.h"

#include <iostream>

namespace sim3D::Utils {

/// Nothing function that prints nothing.
void nothing() {
  std::cout << "... nothing ...\n";
}

/// Debug callback for OpenGL
void GLAPIENTRY DebugCallback(GLenum source, GLenum type, GLuint id, GLenum severity,
                              GLsizei length, const GLchar* message, const void* userParam) {

  if (id == 131169 || id == 131185 || id == 131204 || id == 131218) return;
  std::cout << "------------------------\n";
  std::cout << "OpenGL ERROR " << id << ":\n\t" << message << std::endl;

  switch (source) {
    case GL_DEBUG_SOURCE_API:             std::cout << "Source: API"; break;
    case GL_DEBUG_SOURCE_WINDOW_SYSTEM:   std::cout << "Source: Window System"; break;
    case GL_DEBUG_SOURCE_SHADER_COMPILER: std::cout << "Source: Shader Compiler"; break;
    case GL_DEBUG_SOURCE_THIRD_PARTY:     std::cout << "Source: Third Party"; break;
    case GL_DEBUG_SOURCE_APPLICATION:     std::cout << "Source: Application"; break;
    case GL_DEBUG_SOURCE_OTHER:           std::cout << "Source: Other"; break;
  } std::cout << std::endl;


  switch (type) {
    case GL_DEBUG_TYPE_ERROR:               std::cout << "Type: API"; break;
    case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: std::cout << "Type: Deprecated Behavior"; break;
    case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  std::cout << "Type: Undefined Behavior"; break;
    case GL_DEBUG_TYPE_PORTABILITY:         std::cout << "Type: Portability"; break;
    case GL_DEBUG_TYPE_PERFORMANCE:         std::cout << "Type: Performance"; break;
    case GL_DEBUG_TYPE_MARKER:              std::cout << "Type: Marker"; break;
    case GL_DEBUG_TYPE_PUSH_GROUP:          std::cout << "Type: Push Group"; break;
    case GL_DEBUG_TYPE_POP_GROUP:           std::cout << "Type: Pop Group"; break;
    case GL_DEBUG_TYPE_OTHER:               std::cout << "Type: Other"; break;
  } std::cout << std::endl;

  switch (severity) {
    case GL_DEBUG_SEVERITY_HIGH:         std::cout << "Severity: High"; break;
    case GL_DEBUG_SEVERITY_MEDIUM:       std::cout << "Severity: Medium"; break;
    case GL_DEBUG_SEVERITY_LOW:          std::cout << "Severity: Low"; break;
    case GL_DEBUG_SEVERITY_NOTIFICATION: std::cout << "Severity: Notification"; break;
  } std::cout << std::endl;
  std::cout << std::endl;
}

auto RenderUI(ImGuiIO& io) -> void {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGui::BeginMainMenuBar();
    if (ImGui::BeginMenu("File")) {
      ImGui::MenuItem("New");
      ImGui::MenuItem("junk");
      ImGui::EndMenu();
    }
    ImGui::EndMainMenuBar();

    ImGui::Begin("Stats");
    ImGui::Text("FPS: %.1f", io.Framerate);
    ImGui::Text("Frame time %.3f ms", 1000.0f / io.Framerate);
    ImGui::End();

    ImGui::Begin("Controls");
    if (ImGui::CollapsingHeader("Box Controls", ImGuiTreeNodeFlags_None)) {
      // ImGui::SliderFloat("x", &box_width, 0.01f, 10.0f);
      // ImGui::SliderFloat("y", &box_height, 0.01f, 10.0f);
      // ImGui::SliderFloat("z", &box_depth, 0.01f, 10.0f);
    }
    if (ImGui::CollapsingHeader("Particle Controls", ImGuiTreeNodeFlags_None)) {
      // ImGui::SliderFloat("radius", &ball_radius, 0.01f, 1.0f);
    }
    ImGui::End();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

}
